#include "client_controller.h"

/* constructor */
/******************************************/
client_controller::client_controller(int server_port)
{
	this->server_port = server_port;
}

/* init client UDP connection */
/******************************************/
void
client_controller::init()
{
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
  
    memset(&servaddr, 0, sizeof(servaddr)); 
      
    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(this->server_port); 
    servaddr.sin_addr.s_addr = INADDR_ANY;

    // init port handler
    p_handler(/* socket parameters */); // ------------->>>>>>>>>> implement
}


/* run client --> get remote file */
/******************************************/
int
client_controller::get_remote_file(char* file_name) { 

	// 01. send request (file name)
    data_packet request();
    request.set_data(file_name);
    p_handler.send(request.to_string());

    // 02. receive ack
    char* buffer;
    p_handler.receive(buffer); // blocking receive
    ack_packet response = packet_parser::parse_ack_packet(buffer);
    int expected_packets_count = response.get_seq_no();

	// 02. implement strategy
    vector<data_packet> received_packets;
    strategy = new saw_client(/* socket parameters */); // ------> implement
    strategy.init(expected_packets_count, &received_packets);
    strategy.implement();
    // sort packets ------------------------------------------->> implement

	// 03. save file to disk
    string file = packet_manager::assemble_data(&received_packets);
    io_handler.save_file(file, store_dir+file_name);
} 