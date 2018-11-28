#ifndef PACKET_MANAGER_H
#define PACKET_MANAGER_H

/* import libraries */
/******************************************/
#include <vector>
#include <string>
#include "../transport_packet/packet.h"
using namespace std;

/* class definition */
/******************************************/
class packet_manager
{
	public:
		static void disassemble_data(char *data, vector<packet> *packet_queue);
		static void assemble_data(vector<packet> *packet_queue, char* data);

	private:
		// prevent instance
		packet_manager();
};

#endif 
