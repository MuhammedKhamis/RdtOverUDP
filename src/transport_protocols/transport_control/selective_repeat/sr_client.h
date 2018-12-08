#ifndef SR_CLIENT_H
#define SR_CLIENT_H

/* import libraries */
/******************************************/
#include <vector>

#include "selective_repeat.h"
#include "../../../transport_packet/data_packet.h"
#include "../../../transport_packet/ack_packet.h"

using namespace std;

/* class definition */
/******************************************/
class sr_client : public selective_repeat
{
	private:
		// attributes
		int expected_packets_count;
		vector<data_packet*> *received_packets;

	public:
		// constructor
		sr_client(port_handler *p);
		
		//interface methods
		void init(int expected_packets_count, vector<data_packet*> *received_packets);
		void implement();
		
};

#endif 
