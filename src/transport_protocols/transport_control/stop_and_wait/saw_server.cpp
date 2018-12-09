#include "saw_server.h"

/* constructor */
/******************************************/
saw_server::saw_server(port_handler *p) : stop_and_wait(p) {}

/* init */
/******************************************/
void
saw_server::init(vector<data_packet*> &data_packets)
{
	this->data_packets = data_packets;
	ack_packet ak(data_packets.size());
	p_handler->send(ak.to_string());
}

/* implement strategy */
/******************************************/
void saw_server::implement()
{
    vector<data_packet*>::iterator ptr;
    for (ptr = data_packets.begin(); ptr < data_packets.end(); ptr++)
    {
        while(1)
        {
            data_packet* curr_pkt = *ptr;
            // 01. send packet
            string send_data =  curr_pkt->to_string();

            p_handler->send(send_data);
            // 02. simulate packet loss
                // loss_simulator.simulate();
                // if true lose packet

            // 03. wait for the ack
            // BLOCKING receive
            // we give p_handler a TIMEOUT to stop listening to port, i.e. packet loss happened
            string buffer;
            int receive_flag = p_handler->receive(buffer);
            if(receive_flag == 0){continue;} // timed-out, or packet loss -> resend packet

            // 04. check seq no
            // received ack seq_no will always be the one i just sent
            delete curr_pkt;
            break; // send next packet
        }
    }
}