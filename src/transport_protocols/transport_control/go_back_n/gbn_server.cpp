#include "gbn_server.h"

/* constructor */
/******************************************/
gbn_server::gbn_server(port_handler *p) : go_back_n(p) {
    pthread_mutex_init(&lock, NULL);
}

/* interface method */
/******************************************/

void gbn_server::init(float plp, int seed, vector<data_packet*> &data_packets) {

    this->data_packets = data_packets;
    ack_packet ak(data_packets.size());
    p_handler->send(ak.to_string());

    // setting the random generator for packet loss.
    rg = random_generator(plp, seed, data_packets.size());
}

/* interface method */
/******************************************/
void
gbn_server::implement()
{
    int number_pkts = data_packets.size();
    int base, next_seq_num;
    base = next_seq_num = 0;
    while (base < number_pkts){

        int window_size = cg.get_curr_window_size();
        window_size_analysis.emplace_back(window_size);

        //loop the size of the window, or the remaining of not-send packets
        int remaining = min(number_pkts-base, window_size);

        for(; next_seq_num < (base+remaining); next_seq_num++){
            send_packet(next_seq_num);
        }
        string buffer;
        if(p_handler->receive(buffer, window_size) == 0){
            //Timeout -> resend all again.
            cg.update_window_size(TIMEOUT);
            next_seq_num = base;
            continue;
        }else{
            ack_packet *pkt = packet_parser::create_ackpacket(buffer);
            uint32_t seqno = pkt->get_seqno();
            ack_packet check_pkt(seqno);
            if(checksum_calculator::validate(pkt->get_checksum(), check_pkt.get_checksum())){
                // correct pkt
                if(seqno == base){
                    // expected seqno
                    base++;
                    cg.update_window_size(ACK);
                    successful_sent++;
                }
                // ignore otherwise
            }
        }
    }
}


/* utility method */
/******************************************/
void
gbn_server::send_packet(int seq_no)
{

    // get packet by seq_no
    data_packet *curr_pkt = data_packets[seq_no];

    // send packet to client
    if(rg.can_send(seq_no)) {
        // will send if it's defined as loss.
        int r = p_handler->send(curr_pkt->to_string());
        cout << "Packet with seqno = " << seq_no << " will be sent\n";
    }else{
        cout << "Packet with seqno = " << seq_no << " will be lost\n";
    }
    total_sent++;
}

void* gbn_server::run_sender_thread(void *tmp) {
    ((gbn_server*) tmp)->send_handler();
    pthread_exit(NULL);
}

void gbn_server::send_handler() {

}

void* gbn_server::run_receiver_thread(void *tmp) {
    ((gbn_server*) tmp)->recv_handler();
    pthread_exit(NULL);
}

void gbn_server::recv_handler() {

    int ack_pkts_counter = 0;

    while (ack_pkts_counter < data_packets.size()){

        string buffer;
        p_handler->receive(buffer);
        ack_packet *packet = packet_parser::create_ackpacket(buffer);

        // update window
        uint32_t pkt_seq_no = packet->get_seqno();
        ack_packet ack(pkt_seq_no);

        if(checksum_calculator::validate(packet->get_checksum(), ack.get_checksum())){


            pthread_mutex_lock(&lock);
            // expected sequence == recv_seq_no
            if(pkt_seq_no == ack_pkts_counter) {
                int wz = cg.update_window_size(ACK);
                window_size_analysis.emplace_back(wz);
                glob_base = pkt_seq_no + 1;
                ack_pkts_counter++;
            }
            pthread_mutex_unlock(&lock);
        }
        delete packet;
    }
}