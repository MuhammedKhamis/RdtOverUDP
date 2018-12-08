#include "connection_handler.h"

/* constructor */
/******************************************/

connection_handler::connection_handler(struct sockaddr_in client, string file_packet, socklen_t client_len)
        : curr_client(client), file_packet(file_packet), client_len(client_len) {

    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));

    file_dir = string(cwd);

    // Creating socket file descriptor
    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    p = new port_handler(socket_fd, &this->curr_client, &this->client_len);
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

    char *data = (char*)malloc(len);

    // 01. read file from disk
    io_handler::readData(file_name, data, len);

    // 02. disassemble file into packets
	uint32_t seq_start = 0;
    vector<data_packet*> file_packets;
    cout << "hello1 **************************" << endl;
    cout << "data : " << len << endl;
    string data_string(data, len);

    file_packets = packet_manager::disassemble_data(data_string, seq_start);
    // send number of packets as ack packet


    // 03. implement RDT strategy
    sr_server *strategy = new sr_server(p);
    strategy->init(file_packets);
	strategy->implement();
    cout << "we're out *********************" << endl;
    free(data);
}

connection_handler::~connection_handler() {
    //delete strategy;
    delete p;
}