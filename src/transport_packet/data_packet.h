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
  private:
    // attributes
    string data;

  public:
    // constructor
    data_packet();
    data_packet(uint16_t check_sum, uint16_t length, uint32_t seq_no, string data);
    virtual ~data_packet();

    string get_data();

    string to_string();

};

#endif 
