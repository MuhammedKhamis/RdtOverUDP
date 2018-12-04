//
// Created by abdelrhman on 12/2/18.
//

#include <packet_parser.h>
#include "packet.h"

packet::packet(uint16_t check_sum, uint16_t length) : check_sum(check_sum), length(length) {}

packet::~packet() {

}

uint16_t packet::getCheck_sum() const {
  return check_sum;
}

uint16_t packet::getLength() const {
  return length;
}

void packet::setCheck_sum(uint16_t check_sum) {
  packet::check_sum = check_sum;
}

void packet::setLength(uint16_t length) {
  packet::length = length;
}

string packet::to_string() {
  return packet_parser::packet_tostring(this);
}
