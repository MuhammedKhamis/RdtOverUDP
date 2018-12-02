#include <data_packet.h>
#include <ack_packet.h>
#include <sstream>
#include "packet_manager.h"
#include <boost/lexical_cast.hpp>

// -- Data in packets structure

// -----------------------------------------
//
//   -Checksum : number\r\n
//   -Length : number\r\n
//   -Seq_number : number\r\n
//   -Last_packet : 0/1\r\n\r\n
//   -Data : \r\n
//   -Line 1 data
//   -Line 2 data
//          .
//          .
//          .
//          .
// -----------------------------------------


string packet_manager::assemble_packet(data_packet packet_n) {
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
}

vector<data_packet> packet_manager::disassemble_packet(string data) {
  stringstream* s = new stringstream(data);
  uint16_t checksum = get_line_data(s,"Checksum") ;
  uint16_t length = get_line_data(s,"Length") ;
  uint32_t seq_no = get_line_data(s,"Seq_no") ;
  bool last_packet = get_line_data(s,"Last_packet") ;
  string file_data(s->str().substr(s->tellg()));


  vector<data_packet> data_divide;
  for(int i = 0 ; i < file_data.size() ; i += 500){
    string chunk = file_data.substr(i,i+500) ;
    data_divide.push_back(data_packet(checksum, length, seq_no, chunk, last_packet)) ;
  }
  return data_divide;
}

int packet_manager::get_line_data(stringstream* s, string header) {
  string token;
  *s >> token ;
  if(token != header)
    throw std::invalid_argument( "Wrong packet format" );
  *s >> token ;
  if(token != ":")
    throw std::invalid_argument( "Wrong packet format" );
  *s >> token ;
  try
  {
    return  boost::lexical_cast<int>(token); // double could be anything with >> operator.
  }
  catch(...) {
    throw std::invalid_argument( "Wrong packet format" );
  }
}

string packet_manager::assemble_data(vector<packet> packet_queue) {
  throw std::invalid_argument( "Not implemented" );
}
