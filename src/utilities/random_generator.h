#ifndef RANDOM_GENERATOR_H
#define RANDOM_GENERATOR_H


#include <bits/stdc++.h>
using namespace std;

class random_generator {

private:
    float given_plp;
    set<int> lost_seqno;
    unsigned int random_seed;
    void init_generator(int size);

public:
    random_generator();
    random_generator(float plp, unsigned int seed, int size);
    bool can_send(int seqno);


};
#endif //PORT_HANDLER_H
