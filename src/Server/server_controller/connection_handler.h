#ifndef CONNECTION_HANDLER_H
#define CONNECTION_HANDLER_H

/* import libraries */
/******************************************/
#include <vector>
#include <string>
#include "../../transport_protocols/transport_control/rdt_strategy.h"
#include "../../transport_protocols/transport_control/stop_and_wait.h"
#include "../../transport_protocols/transport_control/selective_repeat.h"

using namespace std;

/* class definition */
/******************************************/
class connection_handler
{
	public:
		void handle_client();
};

#endif 
