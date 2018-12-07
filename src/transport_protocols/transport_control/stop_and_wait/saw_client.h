#ifndef SAW_CLIENT_H
#define SAW_CLIENT_H

/* import libraries */
/******************************************/
#include <vector>

#include "stop_and_wait.h"
#include "../../../transport_packet/data_packet.h"
#include "../../../transport_packet/ack_packet.h"

using namespace std;

/* class definition */
/******************************************/
class saw_client : public stop_and_wait
{
	private:
		// attributes
		int expected_packets_count;
		vector<data_packet*> *received_packets;

	public:
		// constructor
		saw_client(port_handler *p);
		
		//interface methods
		void init(int expected_packets_count, vector<data_packet*> *received_packets);
		void implement();
		
};

#endif 
