#ifndef SR_SERVER_H
#define SR_SERVER_H

/* import libraries */
/******************************************/
#include <vector>
#include <pthread.h>

#include "selective_repeat.h"
#include "../../../transport_packet/data_packet.h"
#include "../../congestion_control/congestion_controller.h"
#include "../../transport_control/utilities/packet_window.h"

using namespace std;
#define TIMEOUT 1 // in seconds
#define INIT_WIN_LEN 10

/* class definition */
/******************************************/
class sr_server : public selective_repeat
{
	private: 
		// attributes
		vector<data_packet*> data_packets;
		congestion_controller con_controller;
		circular_array p_window;
		int implementation_done_flag = 0; // used to kick 
		pthread_t time_handler_id;
		
		// utility methods
		void send_packet(int index);
		void* run_timer_thread(void *tmp);
		void timer_handler();

	public:
		// constructor
		sr_server(port_handler *p);
		
		//interface methods
		void init(vector<data_packet*> &data_packets);
		void implement();
};

#endif 
