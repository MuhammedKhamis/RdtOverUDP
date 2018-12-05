#ifndef RDT_STRATEGY_H
#define RDT_STRATEGY_H

/* import libraries */
/******************************************/
#include "../utilities/port_handler.h"

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

		// interface methods
		virtual void implement() = 0;
};

#endif 
