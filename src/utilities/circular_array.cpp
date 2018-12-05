#include "circular_array.h"

/* constructor */
/******************************************/
circular_array::circular_array(int size)
{
	this->data_array(size);
	start = 0;
	end = 0;
}

/* interface methods */
/******************************************/
int
circular_array::insert(struct packet_info pkt)
{
	if(is_full() == 1){return 0;}
	data_array[end] = pkt;
	if(end == data_array.length() - 1)
	{
		end = 0;
		return 1;
	}
	end++;
	return 1;
}

void
circular_array::mark_acked(int seq_no)
{

}

int
circular_array::is_full()
{

}

vector<packet_info>::iterator
circular_array::get_data_array();