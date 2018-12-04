/* import libraries */
/******************************************/
#include "selective_repeat.h"
using namespace std;

/* class definition */
/******************************************/


selective_repeat::selective_repeat(struct sockaddr_in client, int socket_fd, socklen_t client_len)
        : rdt_strategy(client,socket_fd, client_len) {}

void selective_repeat::implement(vector<data_packet> *packets) {
    //TODO
}