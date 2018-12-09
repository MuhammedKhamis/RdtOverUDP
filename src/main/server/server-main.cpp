/* import libraries */
/*************************************/
#include <bits/stdc++.h>
#include <transport_control/utilities/packet_window.h>
#include "../../server_controller/server_controller.h"
using namespace std;

/* main function */
/*************************************/
int
main(int argc, char const *argv[]) 
{

    chdir("../../../data/server/");
    server_controller sc(8000);
    if(sc.init_server()){
        sc.run_server();
    }
    return 0; 
}