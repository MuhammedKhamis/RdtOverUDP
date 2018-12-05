#ifndef CONGESTION_CONTROL_H
#define CONGESTION_CONTROL_H

/* import libraries */
/******************************************/
#include <vector>
#include <string>
#include "state.h"
using namespace std;

/* class definition */
/******************************************/
class congestion_control : public state
{
   public:
    state* update_window(EVENT_TYPE, int *threshold, int *window_size);
};

#endif 
