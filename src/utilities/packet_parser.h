#ifndef PACKET_PARSER_H
#define PACKET_PARSER_H

/* import libraries */
/******************************************/
#include <vector>
#include <string>
#include "../transport_packet/packet.h"

using namespace std;

/* class definition */
/******************************************/
class packet_parser
{
	public:
		// interface methods
		static packet *parse_packet(char* rdt_msg);

	private:
		// prevent instance
		packet_parser();
		// utility methods
		static void tokenize(string target_line, vector<string> *result_tokens);
};

#endif 
