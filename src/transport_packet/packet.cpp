#include "packet.h"

/* constructor */
/******************************************/
packet::packet(uint32_t seq_no): seq_no(seq_no){

}

packet::packet(uint32_t seq_no, uint16_t len, uint16_t checksum)
    : length(len), check_sum(checksum), seq_no(seq_no) {

}

/* setters and getters */
/******************************************/
u_int32_t
packet::get_seqno() const {
  return seq_no;
}


uint16_t
packet::get_checksum() const
{
  return check_sum;
}

uint16_t
packet::get_length() const
{
  return length;
}

string packet::handle_number_sz(uint32_t num, int expected) {
    string str_num = ::to_string(num);
    while (str_num.length() < expected){
        str_num = "0" + str_num;
    }
    return str_num;
}


string
packet::stringfy_header() {
    string res = "" ;
    res += "Checksum: " + handle_number_sz(get_checksum(), 5) + "\r\n";
    res += "Length: " + handle_number_sz(get_length(), 5) + "\r\n";
    res += "Seq_number: " + handle_number_sz(get_seqno(), 10) + "\r\n";
    res += "\r\n";
    return res;
}

/* interface methods */
/******************************************/
