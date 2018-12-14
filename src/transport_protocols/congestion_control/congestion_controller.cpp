#include "congestion_controller.h"
#include "states/slow_start.h"
#include "states/congestion_control.h"

/* constructor */
/******************************************/
congestion_controller::congestion_controller()
{
	this->threshold = INITIAL_THRESHOLD;
	this->window_size = 1;


	state *slow_s = new slow_start(&threshold, &window_size);
	state *congestion_c = new congestion_control(&threshold, &window_size);
	this->curr_state = slow_s;

	slow_s->set_next_state(congestion_c);
	congestion_c->set_next_state(slow_s);
}

/* interface methods */
/******************************************/
int
congestion_controller::update_window_size(EVENT_TYPE event)
{
	curr_state = curr_state->update_window_size(event);
	return window_size;
}

int congestion_controller::get_curr_window_size() {
	return window_size;
}
