//
// Created by muhammed on 02/11/18.
//

#ifndef PORT_HANDLER_H
#define PORT_HANDLER_H
/**
 * Used to handle data given through socket
 * */

#include <bits/stdc++.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <constants.h>
#include <utilities/packet_parser.h>

using namespace std;

class port_handler{
    private:
        int socked_fd;
        struct sockaddr_in *else_addr;
        socklen_t *else_len;
    public:

        port_handler();
        port_handler(int &socked_fd, struct sockaddr_in *else_addr,socklen_t *else_len);

        void send(string data);
        int receive(char *buffer); // blocking receive
        int receive(char *buffer, int timout); // non-blocking. timout in milli-seconds



private:
    int write(char *buffer, int sz);
    int writeExact(char *buffer, int sz);

    int tryRead(char* total , int sz);

    int read(char* total , int sz);
    int readExact(char* total , int sz);

    int closeConnection();
};

#endif //PORT_HANDLER_H
