//
// Created by muhammed on 15/12/18.
//

#ifndef RDTSERVER_GBN_CLIENT_H
#define RDTSERVER_GBN_CLIENT_H

#include "go_back_n.h"
#include "../../../transport_packet/data_packet.h"
#include "../../../transport_packet/ack_packet.h"


class gbn_client: public go_back_n {
private:
    // attributes
    int expected_packets_count;
    vector<data_packet*> *received_packets;

public:
    // constructor
    gbn_client(port_handler *p);

    //interface methods
    void init(int expected_packets_count, vector<data_packet*> *received_packets);
    void implement();


};


#endif //RDTSERVER_GBN_CLIENT_H
