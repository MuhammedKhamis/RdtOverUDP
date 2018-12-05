#ifndef RDT_STRATEGY_H
#define RDT_STRATEGY_H

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
#include "../congestion_control/congestion_controller.h"
#include "packet.h"
#include <data_packet.h>

using namespace std;

/* class definition */
/******************************************/
class rdt_strategy
{
	protected:
		// attributes
		port_handler p_handler;
		
	public:
		// constructor
		rdt_strategy(struct sockaddr_in client, int socket_fd, socklen_t client_len);
		virtual ~rdt_strategy() = default;

		// utility methods
		bool canSend();

		// interface methods
		virtual void implement() = 0;
};

#endif 
