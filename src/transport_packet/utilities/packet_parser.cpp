#include "packet_parser.h"

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
tuple<uint16_t ,uint16_t, uint32_t> packet_parser::get_header_info(vector<string> &tokens) {
  uint16_t checksum = (uint16_t)get_token_value(tokens[CS_IDX]);
  uint16_t len = (uint16_t)get_token_value(tokens[LEN_IDX]);
  uint32_t seqno = get_token_value(tokens[SEQ_IDX]);
  return make_tuple(checksum, len, seqno);
}

uint32_t packet_parser::get_token_value(string line) {
  size_t pos = 0;
  string key ;
  uint32_t value ;
  if ((pos = line.find(": ")) != std::string::npos) {
    key = line.substr(0, pos);
    line.erase(0, pos + 2);
  }

  value = (uint32_t)stoi(line);

  if(key.empty()){
    perror("Header line in request has wrong format\nRequired :\nKey: Value\n") ;
    return -1 ;
  }
  return value;
}


data_packet *packet_parser::create_datapacket(string data) {
  vector<string> tokens = text_handler::tokenize(data, DELM);

  tuple<uint32_t ,uint16_t ,uint16_t > res = get_header_info(tokens);
  uint32_t seqno = get<SEQ_IDX>(res);
  uint16_t len = get<LEN_IDX>(res);
  uint16_t checksum = get<CS_IDX>(res);

  string buffer = "";
  for(int i = SEQ_IDX + 2 ; i < tokens.size(); i++){
    buffer += tokens[i];
    if(i + 1 < tokens.size()){
      buffer += "\r\n";
    }
  }
  return new data_packet(seqno, len, checksum, buffer);
}

ack_packet *packet_parser::create_ackpacket(string data) {
  vector<string> tokens = text_handler::tokenize(data, DELM);

  tuple<uint32_t ,uint16_t ,uint16_t > res = get_header_info(tokens);
  uint32_t seqno = get<SEQ_IDX>(res);
  uint16_t len = get<LEN_IDX>(res);
  uint16_t checksum = get<CS_IDX>(res);

  return new ack_packet(seqno, len, checksum);
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


int packet_parser::get_packet_length(string data) {
    vector<string> tokens = text_handler::tokenize(data, DELM);
    uint16_t len = (uint16_t)get_token_value(tokens[LEN_IDX]);
  return len;
}

packet_parser::packet_parser() {

}
