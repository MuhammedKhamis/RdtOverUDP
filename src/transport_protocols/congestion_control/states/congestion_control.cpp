#include "congestion_control.h"

/* constructor */
/******************************************/
congestion_control::congestion_control(int *threshold, int *window_size)
  : state(threshold, window_size){}

/* interface methods */
/******************************************/
state*
congestion_control::update_window_size(EVENT_TYPE event)
{
  /* timeout event has happened
   * decrease threshold and transfer to slow start state */
  if(event == TIMEOUT)
  {
    *threshold = *window_size / 2 ;
    *window_size = 1 ;
    return next_state;
  }
  /* acknowledgement is received rather than doubling the value of cwnd every RTT,
   * TCP adopts a more conservative approach and increases the value of cwnd by
   * just a single MSS every RTT */
  else if(event == ACK)
  {
    *window_size =  min(*window_size + 1, MAX_WINDOW_SZ) ;
  }
  
  return this ;
}