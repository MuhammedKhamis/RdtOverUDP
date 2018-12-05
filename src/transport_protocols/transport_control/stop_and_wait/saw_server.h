#ifndef SAW_SERVER_H
#define SAW_SERVER_H

/* import libraries */
/******************************************/
#include <vector>
#include <string>
#include "packet.h"
#include "stop_and_wait"
using namespace std;

#define TIMEOUT 1000 // in milli-seconds

/* class definition */
/******************************************/
class saw_server : public stop_and_wait
{
	private:
		// attributes
		vector<data_packet> *packets;

	public:
		// constructor
		saw_server(struct sockaddr_in client, int socket_fd, socklen_t client_len, vector<data_packet> *packets);
		
		//interface methods
		void init(vector<data_packet> *packets);
		void implement() = 0;
		
};

#endif 
