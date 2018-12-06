#include "state.h"

/* constructor */
/******************************************/
state::state(int *threshold, int *window_size)
{
  this->threshold = threshold;
  this->window_size = window_size;
}

/* interface methods */
/******************************************/
void
state::set_next_state(state* next_state)
{
  this->next_state = next_state;
}