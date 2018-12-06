/* import libraries */
/******************************************/
#include "selective_repeat.h"

/* constructor */
/******************************************/
selective_repeat::selective_repeat(struct sockaddr_in client, int socket_fd, socklen_t client_len)
        : rdt_strategy(client,socket_fd, client_len) {}
