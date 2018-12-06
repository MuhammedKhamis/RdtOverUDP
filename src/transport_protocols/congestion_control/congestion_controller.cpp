#include <states/slow_start.h>
#include "congestion_controller.h"

/* constructor */
/******************************************/
congestion_controller::congestion_controller()
{
	this->threshold = INITIAL_THRESHOLD;
	this->window_size = 1;

	state *slow_start = new slow_start(&threshold, &window_size);
	state *congestion_control = new congestion_control(&threshold, &window_size);
	this->curr_state = slow_start;

	slow_start->set_next_state(congestion_control);
	congestion_control->set_next_state(slow_start);
}

/* interface methods */
/******************************************/
int
congestion_controller::update_window_size(EVENT_TYPE event)
{
	curr_state = curr_state->update_window_size(event);
	return window_size;
}
