#ifndef DATA_PACKET_H
#define DATA_PACKET_H

/* import libraries */
/******************************************/
#include <vector>
#include <string>
#include "packet.h"
using namespace std;

/* class definition */
/******************************************/
class data_packet : public packet
{
 public:
  data_packet(uint16_t check_sum, uint16_t length, uint32_t seq_no, string data, bool last_packet);
  virtual ~data_packet();
  uint32_t getSeq_no() const;
  string getData() const;
  void setSeq_no(uint32_t seq_no);
  void setData(string data);
  bool isLast_packet() const;
  void setLast_packet(bool last_packet);
 private:
      uint32_t seq_no;
      string data;
      bool last_packet;
};

#endif 
