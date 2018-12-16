#include "gbn_client.h"



/* constructor */
/******************************************/
gbn_client::gbn_client(port_handler *p) : go_back_n(p) {}

/* init */
/******************************************/
void
gbn_client::init(int expected_packets_count, vector<data_packet*> *received_packets)
{
    this->expected_packets_count = expected_packets_count;
    this->received_packets = received_packets;
}

/* implement strategy */
/******************************************/
void gbn_client::implement()
{
    int received_pkt_count = 0;

    while(received_pkt_count < expected_packets_count)
    {

        string data_string;
        // 01. BLOCKING receive
        int r = p_handler->receive(data_string); // blocking

        // 02. parse packet
        data_packet *curr_pkt = packet_parser::create_datapacket(data_string);
        data_packet comp_pkt(curr_pkt->get_seqno(), curr_pkt->get_data());

        if(checksum_calculator::validate(curr_pkt->get_checksum(), comp_pkt.get_checksum())){
            // packet is valid;

            // 03. send ACK
            ack_packet ack(curr_pkt->get_seqno());
            string ack_string = ack.to_string();

            p_handler->send(ack_string);

            // got the expected.
            if(received_pkt_count == curr_pkt->get_seqno()){

                // 03. add packet to list
                received_packets->push_back(curr_pkt);

                // 04. update variables
                received_pkt_count++;
            }
        }
    }
}