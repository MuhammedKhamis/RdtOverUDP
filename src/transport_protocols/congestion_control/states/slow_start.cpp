#include "slow_start.h"
#include "congestion_control.h"

using namespace std;


//TODO
state * slow_start::update_window(EVENT_TYPE event, int *threshold, int *window_size) {

  /* timeout event has happened
   * decrease threshold and remain in slow start state */
  if(event == TIMEOUT) {
    *threshold = *window_size / 2 ;
    *window_size = MSS ;
  }
  /* acknowledgment is received, increase window size by MSS every ACK*/
  else if(event == ACK) {
    *window_size += MSS ;
  }

  /* when windows reach threshold transfer state to congestion control */
  if(*window_size >= *threshold)
    return congestion_control::inst ;
  else
    return this ;
}

slow_start::slow_start() {

}
