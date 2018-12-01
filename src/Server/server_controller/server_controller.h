#ifndef SERVER_CONTROLLER_H
#define SERVER_CONTROLLER_H

/* import libraries */
/******************************************/
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define MAX_REQ_SZ 1024

using namespace std;

/* class definition */
/******************************************/
class server_controller
{

public:

    server_controller(int port);
    bool init_server();
    void run_server();

protected:

private:

    uint16_t port_no;
    int socket_fd;

	
};

#endif 
