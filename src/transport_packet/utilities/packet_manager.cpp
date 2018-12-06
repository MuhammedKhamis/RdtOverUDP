#include <data_packet.h>
#include <ack_packet.h>
#include <sstream>
#include "packet_manager.h"
#include "packet_parser.h"
#include <boost/lexical_cast.hpp>
#include <bitset>


bool packet_manager::comp(data_packet p1 , data_packet p2){
  return p1.getSeq_no() < p2.getSeq_no() ;
}

string packet_manager::assemble_data(vector<data_packet> packet_queue) {

  // sort data by seq number to be in order
  sort(packet_queue.begin() , packet_queue.end() , comp) ;

  //TODO check packets check sum is good

  // concatenate all packets data set
  string data = "" ;
  for(data_packet p : packet_queue) {
    data += p.getData() ;
  }

  return data ;
}

vector<data_packet> packet_manager::disassemble_data(string data) {
  // sequence number starts from zero for each packet
  uint32_t seq_no = 0 ;
  // parser divide data to chunks
  vector<string> chunks = packet_parser::divide_data_size(data,500) ;

  vector<data_packet> packets;
  for(string chunk : chunks) {
    data_packet packet(get_check_sum(chunk), (uint16_t)chunk.size(), seq_no, chunk) ;
    packets.push_back(packet) ;
    seq_no ++ ;
  }

  return packets ;
}


uint16_t  packet_manager::get_check_sum(string chunk) {

  // divide each chunk to 16-bit pieces (two character)
  vector<string> to_sum = packet_parser::divide_data_size(chunk, 2) ;

  // sum all 16-bit words
  bitset<16> checksum(0) ;
  for( string s : to_sum ) {
    bitset<16> str_bits(s) ;
    checksum = bitset<16>(checksum.to_ulong() + str_bits.to_ulong()) ;
  }

  // obtain 1's compliment of check sum
  for (int i = 0 ; i < checksum.size() ; i++) {
    checksum[i] ^= 1 ;
  }

  return checksum.to_ullong();
}

