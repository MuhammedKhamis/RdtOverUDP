#include "congestion_control.h"
#include "slow_start.h"

using namespace std;

state * congestion_control::update_window(EVENT_TYPE event, int *threshold, int *window_size) {

  /* timeout event has happened
   * decrease threshold and transfer to slow start state */
  if(event == TIMEOUT) {
    *threshold = *window_size / 2 ;
    *window_size = MSS ;
    return new slow_start() ;
  }
  /* acknowledgement is received rather than doubling the value of cwnd every RTT,
   * TCP adopts a more conservative approach and increases the value of cwnd by
   * just a single MSS every RTT */
  else if(event == ACK) {
    *window_size += MSS * MSS / *window_size ;
  }

  return this ;

}
