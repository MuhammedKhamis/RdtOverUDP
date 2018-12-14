#include <io_handler.h>
#include "../../transport_packet/packet.h"
#include "../../transport_packet/utilities/packet_manager.h"
#include <data_packet.h>
#include <port_handler.h>
#include <transport_control/selective_repeat/sr_server.h>
#include "connection_handler.h"
#include "../../transport_protocols/transport_control/stop_and_wait/saw_server.h"

/* constructor */
/******************************************/

connection_handler::connection_handler(struct sockaddr_in client, string file_packet,
        socklen_t client_len, float plp, int seed)
        : curr_client(client), file_packet(file_packet),
        client_len(client_len), plp(plp), seed(seed) {

    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));

    file_dir = string(cwd);

    // Creating socket file descriptor
    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    p = new port_handler(socket_fd, &this->curr_client, &this->client_len);

    //choose the strategy
}
/* interface methods */
/******************************************/
void
connection_handler::handle_client()
{

    //parse datapacket that contain filename.
    data_packet* file_info = packet_parser::create_datapacket(file_packet);

    //get filename
    string file_name = file_info->get_data();

    vector<string> file_lines;

    int len = io_handler::getFileSize(file_name);

    if(len == -1){
        // 404 File not found.
        cout << "File not found\n";
        delete file_info;
        return;
    }

    char *data = (char*)malloc(len);

    // 01. read file from disk
    io_handler::readData(file_name, data, len);

    // 02. disassemble file into packets
	uint32_t seq_start = 0;
    vector<data_packet*> file_packets;
    string data_string(data, len);

    file_packets = packet_manager::disassemble_data(data_string, seq_start);
    // send number of packets as ack packet

    // 03. implement RDT strategy
    auto *strategy = new sr_server(p);
    strategy->init(plp, seed, file_packets);
	strategy->implement();

    strategy->print_window_size_analysis();

	free(data);
    delete file_info;
    delete strategy;
}

connection_handler::~connection_handler() {
    delete p;
}