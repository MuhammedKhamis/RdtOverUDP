//
// Created by muhammed on 15/12/18.
//

#ifndef RDTSERVER_GO_BACK_N_H
#define RDTSERVER_GO_BACK_N_H

#include "../rdt_strategy.h"

class go_back_n : public rdt_strategy{

public:
    go_back_n(port_handler *p);

    virtual void implement() = 0;

};


#endif //RDTSERVER_GO_BACK_N_H
