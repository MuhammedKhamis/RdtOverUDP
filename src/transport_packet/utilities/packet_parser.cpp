#include <stdexcept>
#include <data_packet.h>
#include "packet_parser.h"
#include <constants.h>

// -- Data in packets structure

// -----------------------------------------
//
//   -Checksum : number\r\n
//   -Length : number\r\n
//   -Seq_number : number\r\n\r\n
//   -Line 1 data
//   -Line 2 data
//          .
//          .
//          .
//          .
// -----------------------------------------

/* interface methods */
/******************************************/

int packet_parser::get_line_data(stringstream* s, string header) {
  /*
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
  */
}

vector<string> packet_parser::tokenize(string s, string delimiter) {

  vector<string> tokens ;
  size_t pos = 0;
  std::string token;
  while ((pos = s.find(delimiter)) != std::string::npos) {
    token = s.substr(0, pos);
    tokens.push_back(token);
    s.erase(0, pos + delimiter.length());
  }
  tokens.push_back(s) ;
  return tokens ;

}

uint32_t packet_parser::get_token_value(string line) {
  size_t pos = 0;
  string key ;
  uint32_t value ;
  if ((pos = line.find(": ")) != std::string::npos) {
    key = line.substr(0, pos);
    line.erase(0, pos + 2);
  }

  value = (uint32_t)stoul(line);

  if(key.empty() || value.empty()){
    perror("Header line in request has wrong format\nRequired :\nKey: Value\n") ;
    return -1 ;
  }
  return value;
}


packet *packet_parser::create_datapacket(string data) {
  vector<string> tokens = tokenize(data, DELM);
  uint16_t checksum = (uint16_t)get_token_value(tokens[CS_IDX]);
  uint16_t len = (uint16_t)get_token_value(tokens[LEN_IDX]);
  uint32_t seqno = get_token_value(tokens[SEQ_IDX]);

  string buffer = "";
  for(int i = SEQ_IDX + 2 ; i < tokens.size(); i++){
    buffer += tokens[i];
    if(i + 1 < tokens.size()){
      buffer += "\r\n";
    }
  }
  return new data_packet(checksum, len, seqno, buffer);
}

packet *packet_parser::create_ackpacket(string data) {
    vector<string> tokens = tokenize(data, DELM);
    uint16_t checksum = (uint16_t)get_token_value(tokens[CS_IDX]);
    uint16_t len = (uint16_t)get_token_value(tokens[LEN_IDX]);
    uint32_t seqno = get_token_value(tokens[SEQ_IDX]);
  return new ack_packet(checksum, len, seqno);
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

int packet_parser::get_packet_length(string data) {
    vector<string> tokens = tokenize(data, DELM);
    uint16_t len = (uint16_t)get_token_value(tokens[LEN_IDX]);
  return len;
}

packet_parser::packet_parser() {

}
