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

		static string assemble_data(vector<data_packet> packet_queue);
		static vector<data_packet> disassemble_data(string data);

	private:
		// prevent instance
		packet_manager() = default;


};

#endif 
