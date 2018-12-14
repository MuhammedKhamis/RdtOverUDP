#include <io_handler.h>
#include "rdt_strategy.h"

/* constructor */
/******************************************/
rdt_strategy::rdt_strategy(port_handler *p) {
	p_handler = p;
}


void rdt_strategy::print_window_size_analysis() {
    stringstream ss;
	for(int i  = 0 ; i < window_size_analysis.size() ; i++){
		 ss << i << ", " << window_size_analysis[i] << endl;
	}
	string s = ss.str();
	io_handler::writeData("test1.csv", (char*)s.data(), s.size());
}