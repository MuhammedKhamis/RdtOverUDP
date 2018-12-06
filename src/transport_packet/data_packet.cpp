#include "data_packet.h"

/* constructor */
/******************************************/
data_packet::data_packet(uint16_t check_sum, uint16_t length, uint32_t seq_no, string data, bool last_packet)
	: packet(check_sum,length),
	seq_no(seq_no), data(data), last_packet(last_packet) {}

data_packet::~data_packet() {

}

/* setters and getters */
/******************************************/
uint32_t
data_packet::get_seq_no() const
{
  return seq_no;
}

string
data_packet::get_data() const
{
  return data;
}

void
data_packet::set_seq_no(uint32_t seq_no)
{
  data_packet::seq_no = seq_no;
}

void
data_packet::set_data(string data) {
  data_packet::data = data;
}

/* interface methods */
/******************************************/
bool
data_packet::isLast_packet() const
{
  return last_packet;
}

void
data_packet::setLast_packet(bool last_packet)
{
  data_packet::last_packet = last_packet;
}

