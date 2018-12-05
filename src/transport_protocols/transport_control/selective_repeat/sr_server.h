#ifndef SR_SERVER_H
#define SR_SERVER_H

/* import libraries */
/******************************************/
#include <vector>
#include <string>
#include "rdt_strategy.h"
#include "packet.h"
#include <pthread.h>

using namespace std;
#define TIMEOUT 1 // in seconds


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
		vector<data_packet> *packets;
		congestion_controller con_controller;
		int window_size;
		packet_window p_window;
		int implementation_done_flag = 0; // used to kick 
		pthread_t time_handler_id;
		
		// utility methods
		void send_packet(int index);
		void* run_timer_thread(void *tmp);
		void timer_handler();

	public:
		// constructor
		sr_server(struct sockaddr_in client, int socket_fd, socklen_t client_len);
		//interface methods
		void init(vector<data_packet> *packets);
		void implement();
};

#endif 
