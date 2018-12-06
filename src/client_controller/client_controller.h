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
		// attributes
		rdt_strategy *strategy;
		char* store_dir;
		port_handler p_handler;

	public:
		// constructor
		client_controller(int server_port);

		// interface methods
		void init();
		void get_remote_file(char* file_name);
};

#endif 
