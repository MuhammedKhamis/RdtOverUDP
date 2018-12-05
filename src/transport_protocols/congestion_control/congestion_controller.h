#ifndef CONGESTION_CONTROLLER_H
#define CONGESTION_CONTROLLER_H

/* import libraries */
/******************************************/
#include <vector>
#include <string>
#include "state.h"
using namespace std;


/* class definition */
/******************************************/
class congestion_controller
{
	private:
		// attributes
		int window_size;
		int threshold;

	public:
		// constructor
		congestion_controller(int threshold);
        // interface methods
		int update_window_size(EVENT_TYPE);
		state* cong_state;
};

#endif 
