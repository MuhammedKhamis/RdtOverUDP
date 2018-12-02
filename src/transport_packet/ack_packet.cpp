//
// Created by abdelrhman on 12/2/18.
//

#include "ack_packet.h"

ack_packet::ack_packet(uint16_t check_sum, uint16_t length, uint32_t ackno) : packet(check_sum, length), ackno(ackno) {}

ack_packet::~ack_packet() {

}

uint32_t ack_packet::getAckno() const {
  return ackno;
}

void ack_packet::setAckno(uint32_t ackno) {
  ack_packet::ackno = ackno;
}
