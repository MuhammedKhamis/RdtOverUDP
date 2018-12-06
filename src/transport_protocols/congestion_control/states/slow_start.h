#ifndef SLOW_START_H
#define SLOW_START_H

/* import libraries */
/******************************************/
#include <vector>
#include <string>
#include "state.h"
using namespace std;

/* class definition */
/******************************************/
class slow_start : public state
{
	public:
		// constructor
		slow_start(int *threshold, int *window_size);

		// interface methods
		state* update_window_size(EVENT_TYPE event);
};

#endif 
