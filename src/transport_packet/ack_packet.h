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
		// attributes
		uint32_t ackno;

	public:
		// constructor
		ack_packet(uint16_t check_sum, uint16_t length, uint32_t ackno);
		virtual ~ack_packet();

		// setters and getters
		uint32_t getAckno() const;
		void setAckno(uint32_t ackno);

};

#endif 
