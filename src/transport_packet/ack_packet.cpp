#include "ack_packet.h"

/* constructor */
/******************************************/
ack_packet::ack_packet(uint16_t check_sum, uint16_t length, uint32_t ackno)
: packet(check_sum, length, ackno) {}

ack_packet::~ack_packet() {

}


string ack_packet::to_string() {
  string ret = stringfy_header();
  return ret;
}
