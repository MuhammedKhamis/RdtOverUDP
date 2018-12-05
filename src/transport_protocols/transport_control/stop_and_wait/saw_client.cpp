#include "saw_client.h"

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
void saw_server::implement(vector<data_packet> *packets) {

    int time_in_sec = 10;
    for(int i = 0 ; i < packets->size() ; i++){

        // convert data to string
        data_packet curr = *(packets->begin() + i);
        string buf = curr.to_string();
        int buf_len = buf.size();

        if(canSend()) {
            // send packet.
            port_handler::writeExact(socket_fd, &buf[0], buf_len, &client, client_len);
        }

        vector<char> ret_buffer(MAX_REQ_SZ,0);

        // wait for the ack
        int recv_len = port_handler::timeout_tryread(socket_fd, ret_buffer, MAX_REQ_SZ,
                &client, &client_len, time_in_sec);

        //get len of packet from headers

        // process the ack

        // timeOut happened
        if(recv_len == 0){
            // we will resend it.
            i--;
        }else{
            //read the ack.
            recv_len = port_handler::readExact(socket_fd, ret_buffer, 1, &client, &client_len);
        }

    }

}