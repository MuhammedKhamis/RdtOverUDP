#include "data_packet.h"
/* constructor */
/******************************************/

data_packet::data_packet(uint32_t seq_no, string data) : packet(seq_no), data(data) {
	//calc length
	length = data.size() + HEADER_SZ;
	//calc checksum
    this->check_sum = calc_checksum();
}

data_packet::data_packet(uint32_t seq_no, uint16_t len, uint16_t checksum, string data)
	: packet(seq_no, len, checksum) , data(data) {

}


uint16_t data_packet::calc_checksum() {
    /*
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
    */
    return 0;
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

