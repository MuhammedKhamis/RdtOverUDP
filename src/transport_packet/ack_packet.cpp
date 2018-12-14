#include "ack_packet.h"

/* constructor */
/******************************************/
ack_packet::ack_packet(uint32_t ackno): packet(ackno) {
    length = HEADER_SZ;
    this-> check_sum = calc_checksum();
}

ack_packet::ack_packet(uint32_t ackno, uint16_t len, uint16_t checksum)
    : packet(ackno, len, checksum) {

}

ack_packet::~ack_packet() {

}


string ack_packet::to_string() {
  string ret = stringfy_header();
  return ret;
}
