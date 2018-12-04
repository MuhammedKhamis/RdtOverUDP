#include <io_handler.h>
#include <packet.h>
#include <packet_manager.h>
#include <data_packet.h>
#include "connection_handler.h"

/* constructor */
/******************************************/

connection_handler::connection_handler(struct sockaddr_in client, char* file_name, socklen_t client_len)
        : curr_client(client), file_name(file_name), client_len(client_len) {


    // Creating socket file descriptor
    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    //choose the strategy
	strategy = new stop_and_wait(curr_client, socket_fd, client_len);
}
/* interface methods */
/******************************************/
void
connection_handler::handle_client()
{
    vector<string> file_lines;

	// 01. read file from disk
	io_handler::read_file(file_name, &file_lines);

	// 02. disassemble file into packets
    vector<data_packet> file_packets;
    for(string file_line: file_lines){
        vector<data_packet> line_packets = packet_manager::disassemble_data(file_line);
        file_packets.insert(file_packets.end(), line_packets.begin(), line_packets.end());
    }

    // 03. implement RDT strategy
	strategy->implement(&file_packets);

}

connection_handler::~connection_handler() {
    delete strategy;
    close(socket_fd);
}