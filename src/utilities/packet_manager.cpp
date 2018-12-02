#include <data_packet.h>
#include <ack_packet.h>
#include <sstream>
#include "packet_manager.h"
#include "packet_parser.h"
#include <boost/lexical_cast.hpp>

// -- Data in packets structure

// -----------------------------------------
//
//   -Checksum : number\r\n
//   -Length : number\r\n
//   -Seq_number : number\r\n
//   -Last_packet : 0/1\r\n\r\n
//   -Data : \r\n
//   -Line 1 data
//   -Line 2 data
//          .
//          .
//          .
//          .
// -----------------------------------------






string packet_manager::assemble_data(vector<packet> packet_queue) {
  throw std::invalid_argument( "Not implemented" );
}
