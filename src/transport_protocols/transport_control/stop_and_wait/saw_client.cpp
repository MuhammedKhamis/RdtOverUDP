#include "saw_client.h"

/* constructor */
/******************************************/
saw_client::saw_client(port_handler *p) : stop_and_wait(p) {}

/* init */
/******************************************/
void
saw_client::init(int expected_packets_count, vector<data_packet*> &received_packets)
{
    this->expected_packets_count = expected_packets_count;
    this->received_packets = received_packets;
}

/* implement strategy */
/******************************************/
void saw_client::implement()
{
    int received_pkt_count = 0;

    while(received_pkt_count < expected_packets_count)
    {
        // 01. BLOCKING receive
        char buffer[MAX_REQ_SZ] = {0};
        p_handler->receive(buffer); // blocking

        string data_string = string(buffer);

        // 02. parse packet
        data_packet *curr_pkt = packet_parser::create_datapacket(data_string);

        // 03. send ACK
        ack_packet ack(curr_pkt->get_seqno());
        string ack_string = ack.to_string();

        p_handler->send(ack_string);

        // 03. add packet to list
        received_packets.push_back(curr_pkt);

        // 04. update variables
        received_pkt_count++;
    }
    
}