#include <transport_control/selective_repeat/sr_client.h>
#include "client_controller.h"
#include "../transport_packet/utilities/packet_manager.h"
#include "../utilities/io_handler.h"

/* constructor */
/******************************************/
client_controller::client_controller(int server_port)
    : server_port(server_port){

    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    file_dir = string(cwd);
}

/* init client UDP connection */
/******************************************/
void
client_controller::init()
{
    // Creating socket file descriptor 
    if ( (socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
  
    memset(&else_addr, 0, sizeof(else_addr));
      
    // Filling server information
    else_addr.sin_family = AF_INET;
    else_addr.sin_port = htons(server_port);
    else_addr.sin_addr.s_addr = INADDR_ANY;

    else_len = sizeof(else_addr);

    // init port handler
     p_handler = new port_handler(socket_fd, &else_addr, &else_len); // ------------->>>>>>>>>> implement
}


/* run client --> get remote file */
/******************************************/
int
client_controller::get_remote_file(string file_name) {

	// 01. send request (file name)
    data_packet request(0, string(file_name));
    p_handler->send(request.to_string());

    // 02. receive ack
    string buffer;

    p_handler->receive(buffer); // blocking receive

    ack_packet *response = packet_parser::create_ackpacket(buffer);
    int expected_packets_count = response->get_seqno();
    delete  response;

	// 02. implement strategy
    vector<data_packet*> received_packets;
    sr_client *strategy = new sr_client(p_handler); // ------> implement
    strategy->init(expected_packets_count, &received_packets);
    strategy->implement();
    // sort packets ------------------------------------------->> implement

	// 03. save file to disk
    string file = packet_manager::assemble_data(received_packets);

    io_handler::writeData(file_name, (char*) file.data(), file.size());

    return 0;
} 