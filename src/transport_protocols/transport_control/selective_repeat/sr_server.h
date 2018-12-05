#ifndef SR_SERVER_H
#define SR_SERVER_H

/* import libraries */
/******************************************/
#include <vector>
#include <string>
#include "rdt_strategy.h"
#include "packet.h"

using namespace std;


struct packet_info {
	int seq_no; // packet seq-no
	int acked; // boolean 0,1
	time_t start_time; // start time (timer) for this packet
}

/* class definition */
/******************************************/
class sr_server : public selective_repeat
{
	private: 
		// attributes
		congestion_controller con_controller;
		int window_size;

	public:
		// constructor
		sr_server(struct sockaddr_in client, int socket_fd, socklen_t client_len);
		//interface methods
		void init(vector<data_packet> *packets);
		void implement();
};

#endif 
