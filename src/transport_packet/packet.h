#ifndef PACKET_H
#define PACKET_H

/* import libraries */
/******************************************/
#include <vector>
#include <string>
using namespace std;

/* class definition */
/******************************************/
class packet
{
 public:
  packet();
  packet(uint16_t check_sum, uint16_t length);
  virtual ~packet();
  uint16_t getCheck_sum() const;
  uint16_t getLength() const;
  void setCheck_sum(uint16_t check_sum);
  void setLength(uint16_t length);
 private:
        uint16_t check_sum;
        uint16_t length;
};

#endif 
