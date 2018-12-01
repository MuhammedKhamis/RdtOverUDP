/* import libraries */
/******************************************/
#include "selective_repeat.h"
using namespace std;

/* class definition */
/******************************************/


selective_repeat::selective_repeat(struct sockaddr_in client) : rdt_strategy(client) {}

void selective_repeat::implement(vector<packet> *packets) {
    //TODO
}