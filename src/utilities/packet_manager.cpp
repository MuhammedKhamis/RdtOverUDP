#include <data_packet.h>
#include <ack_packet.h>
#include <sstream>
#include "packet_manager.h"
#include "packet_parser.h"
#include <boost/lexical_cast.hpp>

string packet_manager::assemble_data(vector<data_packet> packet_queue) {
  throw std::invalid_argument( "Not implemented" );
}

vector<data_packet> packet_manager::disassemble_data(string data) {
  throw std::invalid_argument( "Not implemented" );
}