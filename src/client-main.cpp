/* import libraries */
/*************************************/

#include "client_controller/client_controller.h"
#include <bits/stdc++.h>

using namespace std;

/* main function */
/*************************************/
int
main(int argc, char const *argv[]) 
{ 
	// some attributes
	char *file_dir = "test.html";
	// create client obj
    client_controller client();
    client.init();
    // receive remote file
    string remote_file = client.get_remote_file(file_dir);

    return 0; 
}