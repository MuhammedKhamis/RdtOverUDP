#include "client_controller.h"

/* constructor */
/******************************************/
client_controller::client_controller(int server_port)
{
	this->server_port = server_port;
	strategy = new saw_client();
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
}


/* run client --> get remote file */
/******************************************/
int
client_controller::get_remote_file(char* file_name) { 

	// 01. send file name and receive ACK
    // get number of packets to receive
    int expected_packets_count;

	// 02. implement strategy
    vector<data_packet> received_packets;
    strategy = new saw_client();
    strategy.init(expected_packets_count, &received_packets);
    strategy.implement();

	// 03. save file to disk
} 