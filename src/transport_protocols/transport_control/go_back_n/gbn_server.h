//
// Created by muhammed on 15/12/18.
//

#ifndef RDTSERVER_GBN_SERVER_H
#define RDTSERVER_GBN_SERVER_H

#include "go_back_n.h"
#include "../../../utilities/random_generator.h"
#include "../../congestion_control/congestion_controller.h"
#include "../utilities/data_structures.h"

class gbn_server : public go_back_n {
private:
    // attributes
    vector<data_packet*> data_packets;
    pthread_t send_id, recv_id;
    pthread_mutex_t lock;
    random_generator rg;
    congestion_controller cg;
    int glob_base;
    clock_t glob_timer;

    // utility methods
    void send_packet(int index);
    static void* run_sender_thread(void *tmp);
    static void* run_receiver_thread(void *tmp);

    void send_handler();
    void recv_handler();

public:
    // constructor
    gbn_server(port_handler *p);

    //interface methods
    void init(float plp, int seed, vector<data_packet*> &data_packets);
    void implement();
};


#endif //RDTSERVER_GBN_SERVER_H
