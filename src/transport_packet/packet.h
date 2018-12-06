#ifndef PACKET_H
#define PACKET_H

/* import libraries */
/******************************************/
#include <vector>
#include <string>
#include <bits/stdc++.h>

using namespace std;

/* class definition */
/******************************************/
class packet
{
  private:
    // attributes
    uint16_t check_sum;
    uint16_t length;
    uint32_t seq_no;
    string handle_number_sz(uint32_t num, int expected);

protected:
    string stringfy_header();

  public:
    // constructor
    packet();
    packet(uint32_t seq_no, uint16_t check_sum, uint16_t length);
    virtual ~packet() = default;

    // interface methods
    virtual string to_string() = 0;

    // setters and getters
    uint16_t get_checksum() const;
    uint16_t get_length() const;
    u_int32_t get_seqno() const;

    void set_checksum(uint16_t check_sum);
    void set_length(uint16_t length);
    void set_seqno(uint32_t seq_no);

};

#endif 
