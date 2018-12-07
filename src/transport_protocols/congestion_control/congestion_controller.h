#ifndef CONGESTION_CONTROLLER_H
#define CONGESTION_CONTROLLER_H

/* import libraries */
/******************************************/
#include <vector>
#include <string>
#include "states/state.h"
using namespace std;

/* class definition */
/******************************************/
class congestion_controller
{
	private:
		// attributes
		int window_size;
		int threshold;
		state* curr_state;

	public:
		// constructor
		congestion_controller();
		
        // interface methods
		int update_window_size(EVENT_TYPE);
};

#endif 
