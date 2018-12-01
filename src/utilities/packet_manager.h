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
		static vector<packet> disassemble_data(const char *data);
		static char* assemble_data(vector<packet> *packet_queue);

	private:
		// prevent instance
		packet_manager() = default;
};

#endif 
