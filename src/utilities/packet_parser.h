#ifndef PACKET_PARSER_H
#define PACKET_PARSER_H

/* import libraries */
/******************************************/
#include <vector>
#include <string>
#include "../transport_packet/packet.h"
#include <cstring>
#include <data_packet.h>

using namespace std;

/* class definition */
/******************************************/
class packet_parser
{
	public:
		// interface methods
		static data_packet create_packet(string data);
		static string packet_tostring(packet packet_n);
		static pair<string,string> seperate_headers_data(string);
		static vector<string> divide_data_size(string data, int size);

	private:
		// prevent instance
		packet_parser();
		// utility methods
		int get_line_data(stringstream *s, string header);


};

#endif 
