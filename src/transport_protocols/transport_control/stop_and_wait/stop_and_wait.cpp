#include "stop_and_wait.h"

/* constructor */
/******************************************/
stop_and_wait::stop_and_wait(struct sockaddr_in client, int socket_fd, socklen_t client_len)
        : rdt_strategy(client, socket_fd, client_len) {}

