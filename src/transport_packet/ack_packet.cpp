#include <algorithm>
#include "ack_packet.h"
#include "utilities/packet_parser.h"
#include "utilities/checksum_calculator.h"
#include "packet.h"

/* constructor */
/******************************************/
ack_packet::ack_packet(uint32_t ackno): packet(ackno) {
    length = HEADER_SZ;
    this-> check_sum = calc_checksum();
}

ack_packet::ack_packet(uint32_t ackno, uint16_t len, uint16_t checksum)
    : packet(ackno, len, checksum) {

}

uint16_t ack_packet::calc_checksum() {
  string whole_package = this->to_string() ;
  vector<string> tokens = packet_parser::tokenize(whole_package, "\r\n" ) ;
  reverse(tokens.begin(),tokens.end()) ;
  tokens.pop_back();
  reverse(tokens.begin(),tokens.end()) ;

  string with_out_checksum = "" ;
  for(string s : tokens){
    with_out_checksum += s ;
  }

  return checksum_calculator::get_checksum(with_out_checksum) ;
}

ack_packet::~ack_packet() {

}


string ack_packet::to_string() {
  string ret = stringfy_header();
  return ret;
}
