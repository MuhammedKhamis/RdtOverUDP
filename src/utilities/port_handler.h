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
public:

    static int write(int socked_fd, char *buffer, int sz, struct sockaddr_in *dest_addr,socklen_t dest_len);
    static int writeExact(int socked_fd, char *buffer, int sz, struct sockaddr_in *dest_addr,socklen_t dest_len);
    static int timeout_write(int sock, char* buf, int sz, struct sockaddr_in *dest_addr,
            socklen_t dest_len, int timeoutinseconds);

    static int tryRead(int socked_fd, vector<char> &total , int sz, struct sockaddr_in *src_addr,socklen_t *src_len);
    static int timeout_tryread(int sock, vector<char> &buf, int sz, struct sockaddr_in *src_addr,
                    socklen_t *src_len,int timeoutinseconds);

    static int read(int socked_fd, vector<char> &total , int sz, struct sockaddr_in *src_addr,socklen_t *src_len);
    static int readExact(int socked_fd, vector<char> &total , int sz, struct sockaddr_in *src_addr,socklen_t *src_len);
    static int timeout_read (int sock, vector<char> &buf, int sz, struct sockaddr_in *src_addr,
            socklen_t *src_len, int timeoutinseconds);

    static int closeConnection(int socked_fd);

private:
    port_handler();
};

#endif //PORT_HANDLER_H
