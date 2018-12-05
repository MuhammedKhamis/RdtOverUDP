#include <states/slow_start.h>
#include "congestion_controller.h"

using namespace std;

congestion_controller::congestion_controller(int threshold) : threshold(threshold) {
    congestion_controller::cong_state = new slow_start() ;
}

int congestion_controller::update_window_size(EVENT_TYPE event) {
  cong_state = cong_state->update_window(event, &threshold, &window_size) ;
}
