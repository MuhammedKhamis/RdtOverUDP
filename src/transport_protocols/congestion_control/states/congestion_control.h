#ifndef CONGESTION_CONTROL_H
#define CONGESTION_CONTROL_H

/* import libraries */
/******************************************/
#include <vector>
#include <string>
#include "state.h"
using namespace std;

/* class definition */
/******************************************/
class congestion_control : public state
{
	public:
		// constructor
		congestion_control(int *threshold, int *window_size);

		// interface methods
		void set_next_state(state *next_state);
		state* update_window_size(EVENT_TYPE event);
};

#endif 
