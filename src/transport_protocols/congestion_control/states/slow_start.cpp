#include "slow_start.h"

/* constructor */
/******************************************/
slow_start::slow_start(int *threshold, int *window_size)
  : state(threshold, window_size){}

/* interface methods */
/******************************************/
state*
slow_start::update_window_size(EVENT_TYPE event)
{
  /* timeout event has happened
  * decrease threshold and remain in slow start state */
  if(event == TIMEOUT)
  {
    *threshold = *window_size / 2 ;
    *window_size = MSS ;
  }
  /* acknowledgment is received, increase window size by MSS every ACK*/
  else if(event == ACK)
  {
    *window_size += MSS ;
  }

  /* when windows reach threshold transfer state to congestion control */
  if(*window_size >= *threshold)
  {
    return next_state;
  }
  return this;
}