#include "packet.h"

/* constructor */
/******************************************/
packet::packet(uint32_t seq_no, uint16_t check_sum, uint16_t length)
  : seq_no(seq_no), check_sum(check_sum), length(length){

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

char*
packet::get_data() const {
  return data;
}

void
packet::set_seqno(uint32_t seq_no) {
  packet::seq_no = seq_no;
}

void
packet::set_checksum(uint16_t check_sum)
{
  packet::check_sum = check_sum;
}

void
packet::set_length(uint16_t length)
{
  packet::length = length;
}

void
packet::set_data(char *data) {
  packet::data = data;
}

/* interface methods */
/******************************************/
char*
packet::to_string() const{
  string res = "" ;
  res += "Checksum : " + ::to_string(get_checksum()) + "\r\n";
  res += "Length : " + ::to_string(get_length()) + "\r\n";
  res += "Seq_number : " + ::to_string(get_seqno()) + "\r\n";
  res += "\r\n" ;
  res += string(get_data()) ;
  return (char*)res.data();
}
