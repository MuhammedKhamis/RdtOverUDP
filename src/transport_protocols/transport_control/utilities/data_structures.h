//
// Created by muhammed on 15/12/18.
//

#ifndef RDTSERVER_DATA_STRUCTURES_H
#define RDTSERVER_DATA_STRUCTURES_H

#include <constants.h>
#include <bits/stdc++.h>

using namespace std;

struct pkt_in{
    pkt_in() : status(NOT_SEND), start_time(clock()) {}
    PKT_STATUS status;
    clock_t start_time;
};

#endif //RDTSERVER_DATA_STRUCTURES_H
