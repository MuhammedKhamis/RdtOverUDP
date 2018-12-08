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
    // constuctor for sending data packets
    data_packet(uint32_t seq_no, string data);
    // constructor for recv data packets
    data_packet(uint32_t seq_no, uint16_t len, uint16_t checksum, string data);

    virtual ~data_packet();

    string get_data();

    string to_string();

    uint16_t calc_checksum();
};

#endif 
