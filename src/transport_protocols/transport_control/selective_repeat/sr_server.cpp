#include "sr_server.h"

/* constructor */
/******************************************/
sr_server::sr_server(port_handler *p) : selective_repeat(p) {
    pthread_mutex_init(&lock, NULL);
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
    pkts_status[seq_no].start_time = clock();

    if(rg.can_send(seq_no)) {
        // will send if it's defined as loss.
        p_handler->send(curr_pkt->to_string());
        cout << "Packet with seqno = " << seq_no << " will be sent.\n";
    }else{
        cout << "Packet with seqno = " << seq_no << " will be lost.\n";
    }
    total_sent++;
}

void* sr_server::run_sender_thread(void *tmp) {
    ((sr_server*) tmp)->send_handler();
    pthread_exit(NULL);
}

void sr_server::send_handler() {
    int base = 0;
    int number_pkts = data_packets.size();
    clock_t curr_time;

    while (base < number_pkts){

        pthread_mutex_lock(&lock);

        int window_size = cg.get_curr_window_size();

        pthread_mutex_unlock(&lock);

        //loop the size of the window, or the remaining of not send packets
        int remaining = min(number_pkts-base, window_size);

        for(int i = base; ((i-base) < remaining); i++){

            //nothing to do.
            if(pkts_status[i].status == ACKED){
                continue;
            }

            // pkt didn't send in the first place
            if(pkts_status[i].status == NOT_SEND){
                send_packet(i);
                continue;
            }
            //resending pkt in case of timeout
            curr_time = clock();
            if((curr_time - pkts_status[i].start_time) > PKT_LOSS_TIMEOUT){
                //PKT loss
                send_packet(i);

                pthread_mutex_lock(&lock);

                int wz = cg.update_window_size(TIMEOUT);
                window_size_analysis.emplace_back(wz);

                pthread_mutex_unlock(&lock);

                continue;
            }
        }
        while (pkts_status[base].status == ACKED && base < number_pkts){
            base++;
        }

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
        ack_packet ack(pkt_seq_no);

        if(checksum_calculator::validate(packet->get_checksum(), ack.get_checksum())){

            int exists = (received_seq_no.find(pkt_seq_no) != received_seq_no.end());

            if(exists == 1){
                delete packet;
                continue;
            } // packet already received


            pthread_mutex_lock(&lock);

            int wz = cg.update_window_size(ACK);
            window_size_analysis.emplace_back(wz);
            pkts_status[pkt_seq_no].status = ACKED;
            successful_sent++;
            pthread_mutex_unlock(&lock);

            received_seq_no.insert(pkt_seq_no);
            ack_pkts_counter++;

        }
        delete packet;
    }
}