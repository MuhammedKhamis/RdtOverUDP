#include "saw_server.h"

/* constructor */
/******************************************/
saw_server::saw_server(port_handler *p) : stop_and_wait(p) {}

/* init */
/******************************************/
void
saw_server::init(float plp, int seed, vector<data_packet*> &data_packets)
{
	this->data_packets = data_packets;
	ack_packet ak(data_packets.size());
	p_handler->send(ak.to_string());

	rg = random_generator(plp, seed, data_packets.size());
}

/* implement strategy */
/******************************************/
void saw_server::implement()
{
    vector<data_packet*>::iterator ptr;
    for (ptr = data_packets.begin(); ptr < data_packets.end(); ptr++)
    {

        data_packet* curr_pkt = *ptr;
        string send_data =  curr_pkt->to_string();

        while(1)
        {
            if(rg.can_send(curr_pkt->get_seqno())) {
                p_handler->send(send_data);
                cout << "Data packet with seq: " << curr_pkt->get_seqno() << " will be sent\n";
            }else{
                cout << "Data packet with seq: " << curr_pkt->get_seqno() << " will be lost\n";
            }

            // 03. wait for the ack
            // BLOCKING receive
            // we give p_handler a TIMEOUT to stop listening to port, i.e. packet loss happened
            string buffer;
            int receive_flag = p_handler->receive(buffer, 100);
            if(receive_flag == 0){continue;} // timed-out, or packet loss -> resend packet

            // 04. check seq no
            ack_packet* recv_ack = packet_parser::create_ackpacket(buffer);
            ack_packet expected_ack(curr_pkt->get_seqno());
            // received ack seq_no will always be the one i just sent
            if(checksum_calculator::validate(recv_ack->get_checksum(), expected_ack.get_checksum())){
                delete curr_pkt;
                delete recv_ack;
                break; // send next packet
            }
            delete recv_ack;
        }
    }
}