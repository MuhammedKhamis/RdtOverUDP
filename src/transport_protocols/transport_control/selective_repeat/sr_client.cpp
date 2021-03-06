#include "sr_client.h"

/* constructor */
/******************************************/
sr_client::sr_client(port_handler *p) : selective_repeat(p) {}

/* init */
/******************************************/
void
sr_client::init(int expected_packets_count, vector<data_packet*> *received_packets)
{
    this->expected_packets_count = expected_packets_count;
    this->received_packets = received_packets;
}

/* implement strategy */
/******************************************/
void sr_client::implement()
{
    set<int> received_seq_no;

    int received_pkt_count = 0;
    while(received_pkt_count < expected_packets_count)
    {
        // 01. BLOCKING receive
        string buffer;
        p_handler->receive(buffer); // blocking

        // 02. parse packet
        data_packet *curr_pkt = packet_parser::create_datapacket(buffer);
        int pkt_seq_no = curr_pkt->get_seqno();

        cout << pkt_seq_no << " Has Just arrived\n";

        // 03. send ACK
        ack_packet ack(pkt_seq_no);

        if(checksum_calculator::validate(curr_pkt->get_checksum(), ack.get_checksum())){

            p_handler->send(ack.to_string());

            // 03. add packet to list
            int exists = (received_seq_no.find(pkt_seq_no) != received_seq_no.end());
            if(exists == 1){continue;} // packet already received

            // this is a new packet
            received_packets->push_back(curr_pkt);
            received_seq_no.insert(pkt_seq_no);
            received_pkt_count++;

        }
    }

    cout << "End of implement\n";

}