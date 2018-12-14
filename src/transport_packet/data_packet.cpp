#include "data_packet.h"
/* constructor */
/******************************************/

data_packet::data_packet(uint32_t seq_no, string data) : packet(seq_no), data(data) {
	//calc length
	length = this->data.size() + HEADER_SZ;
	//calc checksum
    this->check_sum = calc_checksum();
}

data_packet::data_packet(uint32_t seq_no, uint16_t len, uint16_t checksum, string data)
	: packet(seq_no, len, checksum) , data(data) {

}


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

