#ifndef PACKET_PARSER_H
#define PACKET_PARSER_H

/* import libraries */
/******************************************/
#include <vector>
#include <string>
#include "../transport_packet/packet.h"
#include <cstring>

using namespace std;

/* class definition */
/******************************************/
class packet_parser
{
	public:
		// interface methods
		data_packet create_packet(string data);
		string packet_tostring(data_packet packet_n);
		pair<string,string> seperate_headers_data(string);
		vector<string> divide_data_size(string data, int size);

	private:
		// prevent instance
		packet_parser();
		// utility methods
		int get_line_data(stringstream *s, string header);


};

#endif 
