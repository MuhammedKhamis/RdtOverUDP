#ifndef PACKET_MANAGER_H
#define PACKET_MANAGER_H

/* import libraries */
/******************************************/
#include <vector>
#include <string>
#include "../packet.h"
#include "../data_packet.h"
#include "../ack_packet.h"
#include "packet_parser.h"
#include "../../utilities/constants.h"

#include <sstream>
#include <bitset>


using namespace std;

/* class definition */
/******************************************/
class packet_manager
{
	public:

		static string assemble_data(vector<data_packet*> packet_queue);
		static vector<data_packet*> disassemble_data(string data, uint32_t seq_no);


	private:
		// prevent instance
		packet_manager() = default;
        // get check sum of data
		static uint16_t get_check_sum(string) ;
        // comprator to sort packet in order
		static bool comp(data_packet *p1, data_packet *p2);

};

#endif 
