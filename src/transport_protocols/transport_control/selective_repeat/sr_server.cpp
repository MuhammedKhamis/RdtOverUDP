#include "sr_server.h"

/* constructor */
/******************************************/
sr_server::sr_server(struct sockaddr_in client, int socket_fd, socklen_t client_len)
        : selective_repeat(client,socket_fd, client_len){

    this->con_controller();
	window_size = 1;
}


/* interface method */
/******************************************/
void
sr_server::implement()
{
	
}