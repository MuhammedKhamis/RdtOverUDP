#ifndef CIRCULAR_ARRAY_H
#define CIRCULAR_ARRAY_H

/* import libraries */
/******************************************/
#include <vector>
#include <time.h>
using namespace std;

/* data structures */
/******************************************/
struct packet_info {
	int seq_no; // packet seq-no
	int acked; // boolean 0,1
	time_t start_time; // start time (timer) for this packet
};

/* class definition */
/******************************************/
class circular_array
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
		circular_array();
		circular_array(int size);

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
