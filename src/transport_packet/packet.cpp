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

uint16_t packet::calc_checksum() {

    string whole_package = to_string() ;
    vector<string> tokens = text_handler::tokenize(whole_package, "\r\n" );

    string with_out_checksum = "" ;
    for(int i = 1 ; i < tokens.size(); i++){
        with_out_checksum += tokens[i];
        if(i+1 < tokens.size()){
            with_out_checksum += "\r\n";
        }
    }
    check_sum = checksum_calculator::get_checksum(with_out_checksum) ;
    return check_sum;
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
