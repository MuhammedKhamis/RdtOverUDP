/* import libraries */
/******************************************/
#include <zconf.h>
#include <netinet/in.h>
#include <transport_control/rdt_strategy.h>
#include "selective_repeat.h"

/* constructor */
/******************************************/
selective_repeat::selective_repeat(struct sockaddr_in client, int socket_fd, socklen_t client_len)
        : rdt_strategy(client,socket_fd, client_len) {}
