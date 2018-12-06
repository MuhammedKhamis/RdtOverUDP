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

using namespace std;

class port_handler{
    private:
        int socked_fd, struct sockaddr_in *dest_addr,socklen_t dest_len, struct sockaddr_in *src_addr,socklen_t *src_len;

    public:

        port_handler(int socked_fd, struct sockaddr_in *dest_addr,socklen_t dest_len, struct sockaddr_in *src_addr,socklen_t *src_len);
        void send(char* data, int len);
        int receive(char *buffer, int timout); // non-blocking. timout in milli-seconds
        void receive(char *buffer); // blocking receive



    int write(char *buffer, int sz);
    int writeExact(int socked_fd, char *buffer, int sz, struct sockaddr_in *dest_addr,socklen_t dest_len);
    int timeout_write(int sock, char* buf, int sz, struct sockaddr_in *dest_addr,
            socklen_t dest_len, int timeoutinseconds);

    int tryRead(int socked_fd, vector<char> &total , int sz, struct sockaddr_in *src_addr,socklen_t *src_len);
    int timeout_tryread(int sock, vector<char> &buf, int sz, struct sockaddr_in *src_addr,
                    socklen_t *src_len,int timeoutinseconds);

    int read(int socked_fd, vector<char> &total , int sz, struct sockaddr_in *src_addr,socklen_t *src_len);
    int readExact(int socked_fd, vector<char> &total , int sz, struct sockaddr_in *src_addr,socklen_t *src_len);
    int timeout_read (int sock, vector<char> &buf, int sz, struct sockaddr_in *src_addr,
            socklen_t *src_len, int timeoutinseconds);

    int closeConnection(int socked_fd);
};

#endif //PORT_HANDLER_H
