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
	char file_dir[] = "d.pdf";

	// create client obj
    client_controller client(8000);
    client.init();
    clock_t begin = clock();
    client.get_remote_file(file_dir);
    clock_t last = clock();

    cout << float(last - begin) / CLOCKS_PER_SEC << endl;
    return 0;
}