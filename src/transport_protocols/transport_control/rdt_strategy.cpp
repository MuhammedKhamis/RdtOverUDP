#include "rdt_strategy.h"

/* constructor */
/******************************************/
rdt_strategy::rdt_strategy(struct sockaddr_in client, int socket_fd, socklen_t client_len)
{
	p_handler = port_handler(socket_fd, client, client_len);
}