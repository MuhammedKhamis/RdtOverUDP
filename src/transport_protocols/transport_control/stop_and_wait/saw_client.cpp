#include "saw_client.h"

/* constructor */
/******************************************/
saw_client::saw_client(struct sockaddr_in client, int socket_fd, socklen_t client_len)
        : stop_and_wait(client, socket_fd, client_len) {}

/* init */
/******************************************/
void
saw_client::init(int expected_packets_count, vector<data_packet> *received_packets)
{
    this->expected_packets_count = expected_packets_count;
    this->received_packets = received_packets;
}

/* implement strategy */
/******************************************/
void saw_client::implement()
{
    int received_pkt_count = 0;
    int expected_seq_no = 0;
    int last_ack_seq_no = 1;

    while(received_pkt_count < expected_packets_count)
    {
        // 01. BLOCKING receive
        char *buffer;
        p_handler.receive(buffer); // blocking

        // 02. parse packet
        data_packet curr_pkt = packet_parser::parse_data_packet(buffer);

        // 03. send ACK
        if(curr_pkt.get_seq_no() != expected_seq_no)
        {
            // invalid seq no
            ack_packet ack(last_ack_seq_no);
            p_handler.send(ack.to_string());
            continue;
        }
        // valid seq no
        ack_packet ack(expected_seq_no);
        p_handler.send(ack.to_string());

        // 03. add packet to list
        received_packets->push_back(curr_pkt);

        // 04. update variables
        received_pkt_count++;
        int tmp = last_ack_seq_no;
        last_ack_seq_no = expected_seq_no;
        expected_seq_no = tmp;
    }
    
}