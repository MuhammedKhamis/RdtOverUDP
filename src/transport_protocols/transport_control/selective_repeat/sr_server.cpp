#include <congestion_control/congestion_controller.h>
#include "../../../utilities/random_generator.h"
#include "sr_server.h"

/* constructor */
/******************************************/
sr_server::sr_server(port_handler *p) : selective_repeat(p) {
    pthread_mutex_init(&print_lock, NULL);
}

/* interface method */
/******************************************/

void sr_server::init(float plp, int seed, vector<data_packet*> &data_packets) {

    this->data_packets = data_packets;
    ack_packet ak(data_packets.size());
    p_handler->send(ak.to_string());
    pkts_status.resize(data_packets.size());

    // setting the random generator for packet loss.
    rg = random_generator(plp, seed, data_packets.size());
}

/* interface method */
/******************************************/
void
sr_server::implement()
{
    //pthread_create(&time_handler_id, NULL, run_timer_thread, this);
    pthread_create(&recv_id, NULL, run_receiver_thread, this);
    pthread_create(&send_id, NULL, run_sender_thread, this);

    pthread_join(recv_id, NULL);
    pthread_join(send_id, NULL);
    //pthread_join(time_handler_id, NULL);
}


/* utility method */
/******************************************/
void
sr_server::send_packet(int seq_no)
{

    // get packet by seq_no
    data_packet *curr_pkt = data_packets[seq_no];

    // send packet to client
    pkts_status[seq_no].status = SENT;
    time(&((pkts_status[seq_no]).start_time));

    if(rg.can_send(seq_no)) {
        // will send if it's defined as loss.
        p_handler->send(curr_pkt->to_string());
        //cout << "Packet with seqno = " << seq_no << " will be sent.\n";
    }else{
        //cout << "Packet with seqno = " << seq_no << " will be lost.\n";
    }
}

void* sr_server::run_sender_thread(void *tmp) {
    ((sr_server*) tmp)->send_handler();
    pthread_exit(NULL);
}

void sr_server::send_handler() {
    int base = 0;
    int number_pkts = data_packets.size();
    time_t curr_time;
    int window_size = 1;
    congestion_controller cg;

    while (base < number_pkts){

        //loop the size of the window, or the remaining of not send packets
        int remaining = min(number_pkts-base, window_size);

        int new_window_size = window_size;

        for(int i = base; ((i-base) < remaining); i++){

            //nothing to do.
            if(pkts_status[i].status == ACKED){
                //new_window_size = cg.update_window_size(ACK);
                continue;
            }

            // pkt didn't send in the first place
            if(pkts_status[i].status == NOT_SEND){
                send_packet(i);
                continue;
            }
            //resending pkt in case of timeout
            time(&curr_time);
            if(difftime(curr_time, pkts_status[i].start_time) > PKT_LOSS_TIMEOUT){
                //PKT loss
                cout << "Loss at seq: " << i << endl;
                cout << "time diff = " << curr_time - pkts_status[i].start_time << endl;
                send_packet(i);
                //new_window_size = cg.update_window_size(TIMEOUT);
                continue;
            }
        }

        while (pkts_status[base].status == ACKED && base < number_pkts){
            base++;
        }
        window_size = new_window_size;
    }
}

void* sr_server::run_receiver_thread(void *tmp) {
    ((sr_server*) tmp)->recv_handler();
    pthread_exit(NULL);
}

void sr_server::recv_handler() {

    int ack_pkts_counter = 0;
    set<int> received_seq_no;

    while (ack_pkts_counter < data_packets.size()){

        string buffer;
        p_handler->receive(buffer);
        ack_packet *packet = packet_parser::create_ackpacket(buffer);

        // update window
        uint32_t pkt_seq_no = packet->get_seqno();
        delete packet;


        int exists = (received_seq_no.find(pkt_seq_no) != received_seq_no.end());
        if(exists == 1){continue;} // packet already received

        pkts_status[pkt_seq_no].status = ACKED;
        received_seq_no.insert(pkt_seq_no);

        ack_pkts_counter++;

    }
}