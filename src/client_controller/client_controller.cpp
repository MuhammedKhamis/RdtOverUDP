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
}


/* run client --> get remote file */
/******************************************/
#define MAXLINE 1024 
int
client_controller::get_remote_file(char* file_name) { 

    int n, len; 
    char buffer[MAXLINE];
      
    sendto(sockfd, (const char *)hello, strlen(hello), 
        MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
            sizeof(servaddr)); 
    printf("Hello message sent.\n"); 
          
    n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
                MSG_WAITALL, (struct sockaddr *) &servaddr, 
                &len); 
    buffer[n] = '\0'; 
    printf("Server : %s\n", buffer); 
  
    close(sockfd); 
    return 0; 
} 