#include <data_packet.h>
#include <ack_packet.h>
#include <sstream>
#include "packet_manager.h"
#include "packet_parser.h"
#include <bitset>
#include <constants.h>

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
  vector<string> chunks = text_handler::divide_data_size(data, DATA_SZ) ;

  vector<data_packet*> packets;
  for(string chunk : chunks) {
    data_packet *pkt = new data_packet(seq_no, chunk) ;
    packets.push_back(pkt) ;
    seq_no ++ ;
  }

  return packets ;
}


