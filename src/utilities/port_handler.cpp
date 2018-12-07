//
// Created by muhammed on 02/11/18.
//

#include "port_handler.h"

port_handler::port_handler() {}

port_handler::port_handler(int &socked_fd, struct sockaddr_in *else_addr, socklen_t *else_len)
        :socked_fd(socked_fd), else_addr(else_addr), else_len(else_len){

}

void port_handler::send(string data) {
    char* buff = (char*) data.data();
    int len = data.size();
    writeExact(buff, len);
}

int port_handler::writeExact(char *buffer, int sz) {
    char* ptr = buffer;
    int len = sz;
    while (len  > 0){
        int status = write(ptr, len);
        if(status == -1){
            printf("%s\n", strerror(errno));
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

int port_handler::write(char *buffer, int sz) {
    return sendto(socked_fd, buffer, sz, MSG_CONFIRM, (const struct sockaddr *) else_addr, *else_len);
}


int port_handler::receive(char *buffer) {

    // 01. init an array;
    tryRead(buffer, HEADER_SZ);
    string pkt(buffer);
    int len = packet_parser::get_packet_length(pkt);
    memset(buffer, 0, MAX_REQ_SZ);
    int n  = readExact(buffer, len);
    return n;
}

int port_handler::receive(char *buffer, int timout) {
    fd_set socks;
    struct timeval t;
    FD_ZERO(&socks);
    FD_SET(socked_fd, &socks);
    t.tv_sec = timout;
    int n;
    if (select(socked_fd + 1, &socks, NULL, NULL, &t) && (n = receive(buffer)) != -1)
    {
        return n;
    }
    return 0;
}

int port_handler::readExact(char* total , int sz) {

  int len = sz;
  char* buffer = total;
  while(sz > 0) {;
    int valread = read(buffer, sz) ;
    if(valread < 0){
      return -1;
    }
    if(valread == 0){
        break;
    }
    sz -= valread;
    buffer += valread;
  }
  return len - sz ;
}

int port_handler::read(char* total , int sz) {
    return recvfrom(socked_fd, total, sz, MSG_WAITALL, ( struct sockaddr *) else_addr, else_len);
}

int port_handler::tryRead(char* total , int sz) {
    return recvfrom(socked_fd, total, sz, MSG_WAITALL | MSG_PEEK, ( struct sockaddr *) else_addr, else_len);
}

int port_handler::closeConnection() {
    return close(socked_fd);
}
