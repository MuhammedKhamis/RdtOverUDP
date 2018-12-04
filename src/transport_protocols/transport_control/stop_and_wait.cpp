/* import libraries */
/******************************************/
#include <constants.h>
#include "stop_and_wait.h"
using namespace std;

/* class definition */
/******************************************/


stop_and_wait::stop_and_wait(struct sockaddr_in client, int socket_fd, socklen_t client_len)
        : rdt_strategy(client, socket_fd, client_len) {}

void stop_and_wait::implement(vector<data_packet> *packets) {

    for(data_packet dt : *packets){

        // convert data to string
        string buf = dt.to_string();
        int buf_len = buf.size();

        // send packet.
        sendto(socket_fd, &buf[0], buf_len, MSG_CONFIRM,
                (const struct sockaddr *) &client, client_len);

        vector<char> ret_buffer(MAX_REQ_SZ,0);

        //wait for confirmation.
        int recv_len = recvfrom(socket_fd, &ret_buffer[0], MAX_REQ_SZ, MSG_WAITALL,
                ( struct sockaddr *) &client, &client_len);

    }

}