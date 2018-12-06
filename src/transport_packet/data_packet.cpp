#include "data_packet.h"

/* constructor */
/******************************************/
data_packet::data_packet(uint16_t check_sum, uint16_t length, uint32_t seq_no, string data)
	: packet(seq_no,check_sum,length), data(data) {}

data_packet::~data_packet() {

}

string data_packet::get_data() {
    return data;
}

string data_packet::to_string() {
	string ret = stringfy_header();
	ret += data;
	return ret;
}

