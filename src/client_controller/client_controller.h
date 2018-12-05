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

using namespace std;

/* class definition */
/******************************************/
class client_controller
{
	private:
		port_handler p_handler;
		rdt_strategy *strategy;

	public:
		client_controller(int server_port);
		void init();
		void get_remote_file(char* file_name);
};

#endif 
