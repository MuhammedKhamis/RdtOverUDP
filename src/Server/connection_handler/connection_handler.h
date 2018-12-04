#ifndef CONNECTION_HANDLER_H
#define CONNECTION_HANDLER_H

/* import libraries */
/******************************************/
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "transport_control/rdt_strategy.h"
#include "transport_control/stop_and_wait.h"
#include "transport_control/selective_repeat.h"

using namespace std;

/* class definition */
/******************************************/
class connection_handler
{
	public:
		connection_handler(struct sockaddr_in client, char *file_name, socklen_t client_len);
		~connection_handler();
		void handle_client();

private:
	struct sockaddr_in curr_client;
	rdt_strategy* strategy;
	char* file_name;
	int socket_fd;
	socklen_t client_len;
};

#endif 
