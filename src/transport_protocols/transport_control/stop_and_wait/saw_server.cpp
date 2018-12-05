#include "saw_server.h"

/* constructor */
/******************************************/
saw_server::saw_server(struct sockaddr_in client, int socket_fd, socklen_t client_len)
        : stop_and_wait(client, socket_fd, client_len) {}

/* init */
/******************************************/
void
saw_server::init(vector<data_packet> *packets)
{
	this->packets = packets;
}

/* implement strategy */
/******************************************/
void saw_server::implement() {

    vector<data_packet>::iterator ptr;
    for (ptr = packets->begin(); ptr < packets->end();) 
    {
        // 01. send packet
        char* send_data = ptr->to_string();
        p_handler.send(send_data);

        // 02. simulate packet loss
        // loss_simulator.simulate();
        // if true lose packet

        // 03. wait for the ack
        char *data_buffer;
        int receive_flag = p_handler.receive(data_buffer, TIMEOUT);
        if(receive_flag == 1)// ACK received
        {
            ptr++
            continue;
        }
        // packet loss occurred
        // will resend packet again

    }

}