#ifndef SELECTIVE_REPEAT_H
#define SELECTIVE_REPEAT_H

/* import libraries */
/******************************************/
#include <vector>
#include <string>
#include "rdt_strategy.h"
#include "packet.h"

using namespace std;

/* class definition */
/******************************************/
class selective_repeat : public rdt_strategy
{
	public:
		// constructor
		selective_repeat(struct sockaddr_in client, int socket_fd, socklen_t client_len);
		//interface methods
		virtual void implement() = 0;
};

#endif 
