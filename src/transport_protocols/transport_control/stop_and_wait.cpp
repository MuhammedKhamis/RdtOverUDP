/* import libraries */
/******************************************/
#include "stop_and_wait.h"
using namespace std;

/* class definition */
/******************************************/


stop_and_wait::stop_and_wait(struct sockaddr_in client) : rdt_strategy(client) {}

void stop_and_wait::implement(vector<packet> *packets) {
    //TODO
}