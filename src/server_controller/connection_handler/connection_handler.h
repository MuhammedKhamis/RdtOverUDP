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
#include "transport_control/stop_and_wait/saw_server.h"

using namespace std;

/* class definition */
/******************************************/
class connection_handler
{
	public:
		connection_handler(struct sockaddr_in client, string file_packet,
				socklen_t client_len, float plp, int seed);
		~connection_handler();
		void handle_client();

private:
	struct sockaddr_in curr_client;
	port_handler *p;
	string file_packet;
	int socket_fd;
	socklen_t client_len;
	string file_dir;
	float plp;
	int seed;
};

#endif 
