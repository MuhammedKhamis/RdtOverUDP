#ifndef ACK_PACKET_H
#define ACK_PACKET_H

/* import libraries */
/******************************************/
#include <vector>
#include <string>
#include "packet.h"

using namespace std;

/* class definition */
/******************************************/
class ack_packet : public packet
{
private:
	void calc_checksum();

public:
	// constructor used for sending ack packets
	ack_packet(uint32_t ackno);
	// constructor used for recieving ack packets
	ack_packet(uint32_t ackno, uint16_t len, uint16_t checksum);
	virtual ~ack_packet();
	string to_string();


};

#endif 
