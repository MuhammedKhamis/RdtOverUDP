#ifndef PACKET_WINDOW_H
#define PACKET_WINDOW_H

/* import libraries */
/******************************************/
#include <vector>
#include <time.h>
using namespace std;


/* class definition */
/******************************************/
class packet_window
{
	private: 
		// attributes
		vector<struct packet_info> data_array;
		int start = 0 ;
		int last = 0 ;
		int size;
		// utility methods

	public:
		// constructor
		packet_window();
		packet_window(int size);

		// interface methods
		int insert(struct packet_info pkt); // insert new packets
		int mark_acked(int seq_no); // marks certain packet as acknowledged
		void update_array(int) ; // update window size
        vector<packet_info>::iterator begin(); // returns iterator
		vector<packet_info>::iterator end(); // returns iterator
        packet_info get_index(int index); // get packet_info at index index
        bool is_full() ;
};

#endif 
