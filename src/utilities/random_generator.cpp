#include "random_generator.h"


random_generator::random_generator() {}

random_generator::random_generator(float plp, unsigned int seed, int size)
    : given_plp(plp), random_seed(seed) {
    init_generator(size);
}

void random_generator::init_generator(int size) {
    int number_lost = (int)ceil(given_plp * size);

    srand(random_seed);

    for(int i = 0 ; i < number_lost; i++ ){
        int random_val = rand() % size;
        lost_seqno.insert(random_val);
    }
}

bool random_generator::can_send(int seqno) {
    bool can_send = !lost_seqno.count(seqno);
    lost_seqno.erase(seqno);
    return can_send;
}