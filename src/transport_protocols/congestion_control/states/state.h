#ifndef STATE_H
#define STATE_H

/* import libraries */
/******************************************/
#include <vector>
#include <string>
#include "state.h"
#include <constants.h>
using namespace std;

/* class definition */
/******************************************/
class state
{
	protected:
		// attributes	
		state *next_state;
		int *threshold;
		int *window_size;

	public:
		// constructor
		state(int *threshold, int *window_size);

		// interface methods
		void set_next_state(state *next_state);
		virtual state* update_window_size(EVENT_TYPE event) = 0;
};

#endif 
