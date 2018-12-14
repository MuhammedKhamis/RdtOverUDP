#ifndef SAW_SERVER_H
#define SAW_SERVER_H

/* import libraries */
/******************************************/
#include <vector>
#include "stop_and_wait.h"
#include "../../../transport_packet/data_packet.h"
#include "../../../utilities/random_generator.h"

using namespace std;

#define TIMEOUT 1000 // in milli-seconds

/* class definition */
/******************************************/
class saw_server : public stop_and_wait
{
	private:
		// attributes
		vector<data_packet*> data_packets;
		random_generator rg;

	public:
		// constructor
		saw_server(port_handler *p);
		
		//interface methods
		void init(float plp, int seed, vector<data_packet*> &data_packets);
		void implement();
		
};

#endif 
