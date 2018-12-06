#include "rdt_strategy.h"

/* constructor */
/******************************************/
rdt_strategy::rdt_strategy(struct sockaddr_in client, int socket_fd, socklen_t client_len)
{
	this->p_handler(client, socket_fd, client_len);
}