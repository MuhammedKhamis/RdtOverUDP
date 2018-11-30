#ifndef RDT_STRATEGY_H
#define RDT_STRATEGY_H

/* import libraries */
/******************************************/
#include <vector>
#include <string>
#include "../congestion_control/congestion_controller.h"
using namespace std;

/* class definition */
/******************************************/
class rdt_strategy
{
	protected:
		// attributes
		congestion_controller con_controller;

	public:
		// constructor
		rdt_strategy();
		// interface methods
		virtual void implement() = 0;
};

#endif 
