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
      state* update_window(EVENT_TYPE, int *threshold, int *window_size);
};

#endif 
