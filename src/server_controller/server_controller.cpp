#include <connection_handler/connection_handler.h>
#include "server_controller.h"

server_controller::server_controller(int port, float plp, int seed)
    : port_no(port), plp(plp), seed(seed) {

}

bool server_controller::init_server() {

    struct sockaddr_in servaddr;

    // Creating socket file descriptor
    if ( (socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family    = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(port_no);

    // Bind the socket with the server address
    if ( bind(socket_fd, (const struct sockaddr *)&servaddr,
              sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    return true;
}

void server_controller::run_server() {

    while(1) {
        struct sockaddr_in cliaddr;
        int n;
        socklen_t len;

        memset(&cliaddr, 0, sizeof(cliaddr));

        port_handler p(socket_fd, &cliaddr, &len);
        string buffer;
        n = p.receive(buffer);

        // Fork to another process to handle that connection
        pid_t child = fork();
        if(child < 0){
            // error in fork
        }else if(child == 0){
            // now in child
            auto *ch = new connection_handler(cliaddr, buffer, len, plp, seed);
            ch->handle_client();
            delete ch;
            exit(EXIT_SUCCESS);
        }
        usleep(100);
    }
}
