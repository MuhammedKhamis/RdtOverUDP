#ifndef SELECTIVE_REPEAT_H
#define SELECTIVE_REPEAT_H

/* import libraries */
/******************************************/
#include <vector>
#include <string>
using namespace std;

/* class definition */
/******************************************/
class selective_repeat : public rdt_strategy
{
	public:
		// constructor
		selective_repeat();
		//interface methods
		void implement();
};

#endif 
