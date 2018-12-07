#ifndef PACKET_PARSER_H
#define PACKET_PARSER_H

/* import libraries */
/******************************************/
#include <vector>
#include <string>
#include "../transport_packet/packet.h"
#include <cstring>
#include <data_packet.h>
#include <ack_packet.h>

using namespace std;

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
		static vector<string> divide_data_size(string data, int size);

	private:
		// prevent instance
		packet_parser();
		// utility methods
		static int get_line_data(stringstream *s, string header);
		static vector<string> tokenize(string s, string delimiter);
		static uint32_t get_token_value(string line);
		static tuple<uint16_t ,uint16_t, uint32_t> get_header_info(vector<string> &tokens);


};

#endif 
