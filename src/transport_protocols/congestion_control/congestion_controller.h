#ifndef CONGESTION_CONTROLLER_H
#define CONGESTION_CONTROLLER_H

/* import libraries */
/******************************************/
#include <vector>
#include <string>
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
		congestion_controller();
		// interface methods
		int update_window_size();
};

#endif 
