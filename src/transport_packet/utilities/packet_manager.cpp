#include "packet_manager.h"


bool packet_manager::comp(data_packet *p1 , data_packet *p2){
  return p1->get_seqno() < p2->get_seqno() ;
}

string packet_manager::assemble_data(vector<data_packet*> packet_queue) {

  // sort data by seq number to be in order
  sort(packet_queue.begin() , packet_queue.end() , comp) ;

  // concatenate all packets data set
  string data = "" ;
  for(data_packet *p : packet_queue) {
    data += p->get_data() ;
    delete p;
  }

  return data ;
}

vector<data_packet*> packet_manager::disassemble_data(string data, uint32_t seq_no) {
  // sequence number starts from zero for each packet
  // parser divide data to chunks
  vector<string> chunks = packet_parser::divide_data_size(data, DATA_SZ) ;

  vector<data_packet*> packets;
  for(string chunk : chunks) {
    data_packet *pkt = new data_packet(seq_no, chunk) ;
    packets.push_back(pkt) ;
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
    checksum[i] = checksum[i] ^ 1 ;
  }

  return checksum.to_ullong();
}

