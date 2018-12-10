#include "sr_server.h"

/* constructor */
/******************************************/
sr_server::sr_server(port_handler *p) : selective_repeat(p) {
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond_id, NULL);
    pthread_mutex_init(&print_lock, NULL);
}

/* interface method */
/******************************************/

void sr_server::init(vector<data_packet*> &data_packets) {
    p_window = packet_window(INIT_WIN_LEN);
    this->data_packets = data_packets;
    ack_packet ak(data_packets.size());
    p_handler->send(ak.to_string());
    pkts_status.resize(data_packets.size());
    cout << "data length: " << data_packets.size() << endl;
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
    data_packet *curr_pkt = data_packets.at(seq_no);

    // send packet to client
    time(&(pkts_status[seq_no].start_time));
    p_handler->send(curr_pkt->to_string());

    /*
    // create new entry
    struct packet_info tmp;
    tmp.seq_no = curr_pkt->get_seqno();
    tmp.acked = 0;
    time(&tmp.start_time);
    // insert into window
    p_window.insert(tmp);
    */
}


/* TIMER methods */
/******************************************/
void*
sr_server::run_timer_thread(void *tmp)
{
    ((sr_server*) tmp)->timer_handler();
    pthread_exit(NULL);
}

void
sr_server::timer_handler()
{
    time_t curr_time;
    while(implementation_done_flag == 0)
    {
        vector<struct packet_info>::iterator ptr;
        for (ptr = p_window.begin(); ptr < p_window.end(); ptr++)
        {
            if(ptr->acked == 1){continue;} // acked pkt -> skip
            time(&curr_time); // get system current time
            if(difftime(curr_time, ptr->start_time) < PKT_LOSS_TIMEOUT){continue;} // NOT timed-out --> skip
            // handle timed-out packet
            p_handler->send(data_packets.at(ptr->seq_no)->to_string()); // resend packet
            time(&ptr->start_time); // reset timer
        }
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

    while (base < number_pkts){

        //loop the size of the window, or the remaining of not send packets
        int remaining = min(number_pkts-base, INIT_WIN_LEN);

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
            time(&curr_time);
            if(difftime(curr_time, pkts_status[i].start_time) > PKT_LOSS_TIMEOUT){
                send_packet(i);
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
        delete packet;


        int exists = (received_seq_no.find(pkt_seq_no) != received_seq_no.end());
        if(exists == 1){continue;} // packet already received

        pkts_status[pkt_seq_no].status = ACKED;
        received_seq_no.insert(pkt_seq_no);

        ack_pkts_counter++;

    }
}