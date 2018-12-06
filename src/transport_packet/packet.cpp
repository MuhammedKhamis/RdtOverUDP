#include "packet.h"

/* constructor */
/******************************************/
packet::packet(uint16_t check_sum, uint16_t length) : check_sum(check_sum), length(length) {}

packet::~packet() {

}

/* setters and getters */
/******************************************/
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

/* interface methods */
/******************************************/
char*
packet::to_string()
{
  /*
  string res = "" ;
  res += "Checksum : " + to_string(packet_n.getCheck_sum()) + "\r\n";
  res += "Length : " + to_string(packet_n.getLength()) + "\r\n";
  res += "Seq_number : " + to_string(packet_n.getSeq_no()) + "\r\n";
  if(packet_n.isLast_packet())
    res += "Last_packet : YES\r\n";
  else
    res += "Last_packet : NO\r\n";
  res += "Data : \r\n" ;
  res += string(packet_n.getData()) ;
  return res.c_str();
  */
}
