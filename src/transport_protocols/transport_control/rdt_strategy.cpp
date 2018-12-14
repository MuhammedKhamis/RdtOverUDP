#include "rdt_strategy.h"

/* constructor */
/******************************************/
rdt_strategy::rdt_strategy(port_handler *p) {
	p_handler = p;
}


void rdt_strategy::print_window_size_analysis() {
	for(int i : window_size_analysis){
		cout << i << ", ";
	}
	cout << endl;
}