#ifndef PACKET_H
#define PACKET_H

/* import libraries */
/******************************************/
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <constants.h>

using namespace std;

/* class definition */
/******************************************/
class packet
{
  private:
    // attributes
    string handle_number_sz(uint32_t num, int expected);

protected:
    uint16_t check_sum;
    uint16_t length;
    uint32_t seq_no;
    string stringfy_header();
    virtual void calc_checksum() = 0;

  public:
    // constructor
    packet(uint32_t seq_no);
    packet(uint32_t seq_no, uint16_t len, uint16_t checksum);
    virtual ~packet() = default;

    // interface methods
    virtual string to_string() = 0;

    // setters and getters
    uint16_t get_checksum() const;
    uint16_t get_length() const;
    u_int32_t get_seqno() const;

};

#endif 
