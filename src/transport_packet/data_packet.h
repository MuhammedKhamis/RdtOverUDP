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
    uint32_t seq_no;
    string data;
    bool last_packet;

  public:
    // constructor
    data_packet();
    data_packet(uint16_t check_sum, uint16_t length, uint32_t seq_no, string data, bool last_packet);
    virtual ~data_packet();

    // setters and getters
    uint32_t get_seq_no() const;
    string get_data() const;
    void set_seq_no(uint32_t seq_no);
    void set_data(string data);

    // interface methods
    bool isLast_packet() const;
    void setLast_packet(bool last_packet);
 
};

#endif 
