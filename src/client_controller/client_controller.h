#ifndef CLIENT_CONTROLLER_H
#define CLIENT_CONTROLLER_H

/* import libraries */
/******************************************/
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h>
#include "../utilities/port_handler.h"
#include "../transport_protocols/transport_control/rdt_strategy.h"
#include "../transport_protocols/transport_control/stop_and_wait/saw_client.h"
#include "../transport_packet/utilities/packet_manager.h"
#include "../utilities/io_handler.h"

using namespace std;

/* class definition */
/******************************************/
class client_controller
{
	private:
		// attributes
		saw_client *strategy;
		char* store_dir;
		port_handler *p_handler;
		int server_port;
		int socket_fd;
		struct sockaddr_in else_addr;
		socklen_t else_len;
		string file_dir;

	public:
		//client_controller();
		// constructor
		client_controller(int server_port);


		// interface methods
		void init();
		int get_remote_file(string file_name);
};

#endif 
