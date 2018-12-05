//
// Created by abdelrhman on 12/5/18.
//

#ifndef RDTOVERUDP_STATE_H
#define RDTOVERUDP_STATE_H

#include "../../../constants/constants.h"

class state {
   public:
    state* update_window(EVENT_TYPE, int *threshold, int *window_size);
};

#endif //RDTOVERUDP_STATE_H
