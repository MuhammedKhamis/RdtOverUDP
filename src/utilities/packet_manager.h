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
		vector<data_packet> disassemble_packet(string data);
		string assemble_data(vector<packet> packet_queue);
	private:
		// prevent instance
		packet_manager() = default;
		int get_line_data(stringstream* s, string header);

  string assemble_packet(data_packet packet_n);
};

#endif 
