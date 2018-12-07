#ifndef STOP_AND_WAIT_H
#define STOP_AND_WAIT_H

/* import libraries */
/******************************************/
#include "../rdt_strategy.h"
using namespace std;

/* class definition */
/******************************************/
class stop_and_wait : public rdt_strategy
{
	public:
		// constructor
		stop_and_wait(port_handler *p);
		
		//interface methods
		virtual void implement() = 0;
};

#endif 
