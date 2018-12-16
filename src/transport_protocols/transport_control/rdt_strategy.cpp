#include "rdt_strategy.h"

/* constructor */
/******************************************/
rdt_strategy::rdt_strategy(port_handler *p) {
	p_handler = p;
}


void rdt_strategy::print_window_size_analysis() {
    stringstream ss;
    int sz = min(1000, (int)window_size_analysis.size());
	for(int i  = 0 ; i <  sz; i++){
		 ss << i << ", " << window_size_analysis[i] << endl;
	}
	string s = ss.str();
	io_handler::writeData("test1.csv", (char*)s.data(), s.size());

	cout << float(successful_sent * 1.0 / total_sent) << endl;
}