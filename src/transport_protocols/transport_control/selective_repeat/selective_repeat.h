#ifndef SELECTIVE_REPEAT_H
#define SELECTIVE_REPEAT_H

/* import libraries */
/******************************************/
#include "../rdt_strategy.h"
#include <zconf.h>
#include <netinet/in.h>

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
