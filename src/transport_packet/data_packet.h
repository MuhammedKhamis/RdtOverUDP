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
  data_packet(uint16_t check_sum, uint16_t length, uint32_t seq_no, char *data);
  virtual ~data_packet();
  uint32_t getSeq_no() const;
  char *getData() const;
  void setSeq_no(uint32_t seq_no);
  void setData(char *data);
 private:
      uint32_t seq_no;
      char* data;
};

#endif 
