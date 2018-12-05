#ifndef STOP_AND_WAIT_H
#define STOP_AND_WAIT_H

/* import libraries */
/******************************************/
#include <vector>
#include <string>
#include "rdt_strategy.h"
#include "packet.h"
using namespace std;

/* class definition */
/******************************************/
class stop_and_wait : public rdt_strategy
{
	public:
		// constructor
		stop_and_wait(struct sockaddr_in client, int socket_fd, socklen_t client_len);
		//interface methods
		virtual void implement() = 0;
};

#endif 
