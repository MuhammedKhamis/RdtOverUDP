#include "packet_manager.h"

// -- Data in packets structure

// -----------------------------------------
//
//   -Checksum : number\r\n
//   -Length : number\r\n
//   -Seq_number : number\r\n
//   -Last_packet : YES/NO\r\n\r\n
//   -Data : \r\n
//   -Line 1 data
//   -Line 2 data
//          .
//          .
//          .
//          .
// -----------------------------------------


char* packet_manager::assemble_data(vector<packet> *packet_queue) {
    //TODO
}

vector<packet> packet_manager::disassemble_data(const char *data) {
    //TODO
}
