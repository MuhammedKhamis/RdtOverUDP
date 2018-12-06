#ifndef PACKET_H
#define PACKET_H

/* import libraries */
/******************************************/
#include <vector>
#include <string>
#include "packet_parser.h"
using namespace std;

/* class definition */
/******************************************/
class packet
{
  private:
    // attributes
    uint16_t check_sum;
    uint16_t length;

  public:
    // constructor
    packet();
    packet(uint16_t check_sum, uint16_t length);
    virtual ~packet();

    // interface methods
    char* to_string();

    // setters and getters
    uint16_t get_checksum() const;
    uint16_t get_length() const;
    void set_checksum(uint16_t check_sum);
    void set_length(uint16_t length);
    

};

#endif 
