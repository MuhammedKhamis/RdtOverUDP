#ifndef STOP_AND_WAIT_H
#define STOP_AND_WAIT_H

/* import libraries */
/******************************************/
#include <vector>
#include <string>
using namespace std;

/* class definition */
/******************************************/
class stop_and_wait : public rdt_strategy
{
	public:
		// constructor
		stop_and_wait();
		//interface methods
		void implement();
};

#endif 
