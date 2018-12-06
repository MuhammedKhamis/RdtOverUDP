#include "ack_packet.h"

/* constructor */
/******************************************/
ack_packet::ack_packet(uint16_t check_sum, uint16_t length, uint32_t ackno) : packet(check_sum, length), ackno(ackno) {}

ack_packet::~ack_packet() {

}

/* setters and getters */
/******************************************/
uint32_t
ack_packet::getAckno() const
{
  return ackno;
}

void
ack_packet::setAckno(uint32_t ackno)
{
  ack_packet::ackno = ackno;
}
