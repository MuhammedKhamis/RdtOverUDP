#include "data_packet.h"
/* constructor */
/******************************************/

data_packet::data_packet(uint32_t seq_no, string data) : packet(seq_no), data(data) {
	//calc length
	length = data.size() + HEADER_SZ;
	//calc checksum
    calc_checksum();
}

data_packet::data_packet(uint32_t seq_no, uint16_t len, uint16_t checksum, string data)
	: packet(seq_no, len, checksum) , data(data) {

}


void data_packet::calc_checksum() {
    //TODO
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

