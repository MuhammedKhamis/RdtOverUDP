#ifndef SELECTIVE_REPEAT_H
#define SELECTIVE_REPEAT_H

#include "../rdt_strategy.h"
/* import libraries */
/******************************************/
using namespace std;

/* class definition */
/******************************************/
class selective_repeat : public rdt_strategy
{
	public:
		// constructor
		selective_repeat(port_handler *p);
		//interface methods
		virtual void implement() = 0;
};

#endif 
