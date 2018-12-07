/* import libraries */
/*************************************/

#include <bits/stdc++.h>
#include <client_controller.h>

using namespace std;

/* main function */
/*************************************/
int
main(int argc, char const *argv[]) 
{
    chdir("../../../data/client/");

    // some attributes
	char file_dir[] = "smile.jpeg";

	// create client obj
    client_controller client(8000);
    client.init();
    client.get_remote_file(file_dir);

    return 0;
}