//
// Created by abdelrhman on 12/2/18.
//

#include "data_packet.h"

data_packet::data_packet(uint16_t check_sum, uint16_t length, uint32_t seq_no, string data) : packet(
    check_sum,
    length), seq_no(seq_no), data(data) {}


data_packet::~data_packet() {

}

uint32_t data_packet::getSeq_no() const {
  return seq_no;
}

string data_packet::getData() const {
  return data;
}

void data_packet::setSeq_no(uint32_t seq_no) {
  data_packet::seq_no = seq_no;
}

void data_packet::setData(string data) {
  data_packet::data = data;
}

bool data_packet::isLast_packet() const {
  return last_packet;
}

void data_packet::setLast_packet(bool last_packet) {
  data_packet::last_packet = last_packet;
}

