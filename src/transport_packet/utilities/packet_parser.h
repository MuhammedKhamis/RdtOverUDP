#ifndef PACKET_PARSER_H
#define PACKET_PARSER_H

/* import libraries */
/******************************************/
#include <vector>
#include <string>
#include <cstring>

#include "../data_packet.h"
#include "../ack_packet.h"
#include "../packet.h"
#include <stdexcept>
#include <constants.h>
#include "../../utilities/text_handler.h"

using namespace std;

class data_packet;
class ack_packet;

/* class definition */
/******************************************/
class packet_parser
{
	public:
		// interface methods
		static data_packet *create_datapacket(string data);
        static ack_packet *create_ackpacket(string data);
		static pair<string,string> seperate_headers_data(string);
		static int get_packet_length(string data);

	private:
		// prevent instance
		packet_parser();
		// utility methods
		static uint32_t get_token_value(string line);
		static tuple<uint16_t ,uint16_t, uint32_t> get_header_info(vector<string> &tokens);


};

#endif 
