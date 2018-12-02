#include <stdexcept>
#include <boost/lexical_cast.hpp>
#include <data_packet.h>
#include "packet_parser.h"

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

/* interface methods */
/******************************************/
string packet_parser::packet_tostring(data_packet packet_n) {
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


int packet_parser::get_line_data(stringstream* s, string header) {
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
    return  boost::lexical_cast<int>(token);
  }
  catch(...) {
    throw std::invalid_argument( "Wrong packet format" );
  }
}

data_packet packet_parser::create_packet(string data) {
  stringstream* s = new stringstream(data);
  uint16_t checksum = get_line_data(s,"Checksum") ;
  uint16_t length = get_line_data(s,"Length") ;
  uint32_t seq_no = get_line_data(s,"Seq_no") ;
  bool last_packet = get_line_data(s,"Last_packet") ;
  string file_data(s->str().substr(s->tellg()));
  return data_packet(checksum, length, seq_no, file_data, last_packet) ;
}

pair<string, string> packet_parser::seperate_headers_data(string data) {
  stringstream ss(data);
  string headers,to;
  for( int i = 0 ; i < 4 ; i++){
    getline(ss,to,'\n') ;
    headers += to + "\n" ;
  }
  // Data :
  getline(ss,to,'\n') ;
  string file_data(ss.str().substr(ss.tellg()));
  return {headers,file_data} ;
}

vector<string> packet_parser::divide_data_size(string data , int size = 500){
  vector<string> data_divide;
  for(int i = 0 ; i < data.size() ; i += size){
    string chunk = data.substr(i,i+size) ;
    data_divide.push_back(chunk) ;
}

  return data_divide ;
}


packet_parser::packet_parser() {

}
