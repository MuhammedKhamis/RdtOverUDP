#include "saw_server.h"

/* constructor */
/******************************************/
saw_server::saw_server(struct sockaddr_in client, int socket_fd, socklen_t client_len)
        : stop_and_wait(client, socket_fd, client_len) {}

/* init */
/******************************************/
void
saw_server::init(vector<data_packet> *data_packets)
{
	this->data_packets = data_packets;
}

/* implement strategy */
/******************************************/
void saw_server::implement()
{
    int curr_seq_no = 0;
    int last_seq_no = 1;

    vector<data_packet>::iterator ptr;
    for (ptr = data_packets->begin(); ptr < data_packets->end(); ptr++) 
    {
        while(1)
        {
            // 01. send packet
            ptr->set_seq_no(curr_seq_no);
            char* send_data = ptr->to_string();
            p_handler.send(send_data);

            // 02. simulate packet loss
                // loss_simulator.simulate();
                // if true lose packet

            // 03. wait for the ack
            // BLOCKING receive
            // we give p_handler a TIMEOUT to stop listening to port, i.e. packet loss happened
            char *buffer;
            int receive_flag = p_handler.receive(buffer, TIMEOUT);
            if(receive_flag == 0){continue;} // timed-out, or packet loss -> resend packet

            // 04. check seq no
            // received ack seq_no will always be the one i just sent
            int tmp = last_seq_no;
            last_seq_no = curr_seq_no;
            curr_seq_no = tmp;
            
            break; // send next packet
        }
    }
}