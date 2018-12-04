//
// Created by muhammed on 02/11/18.
//

#include "port_handler.h"


int port_handler::readExact(int socked_fd, vector<char> &total , int sz, struct sockaddr_in *src_addr,
        socklen_t *src_len ) {

  int len = sz;
  while(sz > 0) {
    vector<char> buffer(sz, 0);
    int valread = read(socked_fd, buffer, sz, src_addr, src_len) ;
    if(valread < 0){
      return -1;
    }
    if(valread == 0){
        break;
    }
    sz -= valread;
    string r = string(buffer.begin(), buffer.begin() + ((valread < len) ? valread : len));
    total.insert(total.end(), r.begin(), r.end());
  }
  return len - sz ;
}

int port_handler::read(int socked_fd, vector<char> &total , int sz, struct sockaddr_in *src_addr,socklen_t *src_len ) {
    return recvfrom(socked_fd, &total[0], sz, MSG_WAITALL, ( struct sockaddr *) src_addr, src_len);
}

int port_handler::tryRead(int socked_fd, vector<char> &total , int sz, struct sockaddr_in *src_addr,socklen_t *src_len) {
    return recvfrom(socked_fd, &total[0], sz, MSG_WAITALL | MSG_PEEK, ( struct sockaddr *) src_addr, src_len);
}


int port_handler::timeout_read(int sock, vector<char> &buf, int sz, struct sockaddr_in *src_addr,
        socklen_t *src_len,int timeoutinseconds){
    fd_set socks;
    struct timeval t;
    FD_ZERO(&socks);
    FD_SET(sock, &socks);
    t.tv_sec = timeoutinseconds;
    int n;
    if (select(sock + 1, &socks, NULL, NULL, &t) &&
            (n = readExact(sock, buf, sz, src_addr, src_len)) != -1)
    {
        return n;
    }
    return 0;
}

int port_handler::timeout_tryread(int sock, vector<char> &buf, int sz, struct sockaddr_in *src_addr,
                               socklen_t *src_len,int timeoutinseconds){
    fd_set socks;
    struct timeval t;
    FD_ZERO(&socks);
    FD_SET(sock, &socks);
    t.tv_sec = timeoutinseconds;
    int n;
    if (select(sock + 1, &socks, NULL, NULL, &t) &&
        (n = tryRead(sock, buf, sz, src_addr, src_len)) != -1)
    {
        return n;
    }
    return 0;
}


int port_handler::timeout_write(int sock, char* buf, int sz, struct sockaddr_in *dest_addr, socklen_t dest_len,
        int timeoutinseconds){
    fd_set socks;
     struct timeval t;
     FD_ZERO(&socks);
     FD_SET(sock, &socks);
     t.tv_sec = timeoutinseconds;
     int n;
     if (select(sock + 1, &socks, NULL, NULL, &t) &&
     (n = writeExact(sock, buf, sz, dest_addr, dest_len)) != -1)
     {
         return n;
     }
     return 0;
}

int port_handler::writeExact(int socked_fd, char *buffer, int sz, struct sockaddr_in *dest_addr,socklen_t dest_len) {
  char* ptr = buffer;
  int len = sz;
  while (len  > 0){
    int status = write(socked_fd, ptr, len, dest_addr, dest_len);
    if(status == -1){
      return status;
    }
    if(status == 0){
        break;
    }
    ptr+=status;
    len-=status;
  }
  return sz;
}

int port_handler::write(int socked_fd, char *buffer, int sz, struct sockaddr_in *dest_addr,socklen_t dest_len) {
    return sendto(socked_fd, buffer, sz, MSG_CONFIRM, (const struct sockaddr *) dest_addr, dest_len);
}

int port_handler::closeConnection(int socked_fd) {
    return close(socked_fd);
}
