#include "packet_window.h"

/* constructor */
/******************************************/
circular_array::circular_array(int size)
{
	this->data_array.resize(size);
	this->start = 0 ;
	this->end = 0 ;
	this->size = 0 ;
}

/* interface methods */
/******************************************/
int
circular_array::insert(struct packet_info pkt)
{
	if(is_full() == 1){
		return -1 ;
	}
	data_array[end] = pkt;

	end++ ;
	size++ ;
	end %= data_array.size() ;

	return 1;
}

int
circular_array::mark_acked(int seq_no)
{
	int index = seq_no % data_array.size() ;
	int total_ack = 1 ;

	data_array[index].acked = true ;

	if(index == start) {
		while(data_array[index].acked){
			index += 1 ;
			index %= size ;
			total_ack ++ ;
		}
		start = index ;
	}

	size -= total_ack ;

	return total_ack ;
}

bool
circular_array::is_full()
{
	this->size == data_array.size() ;
}

vector<packet_info>::iterator
circular_array::begin(){
	return data_array.begin() ;
}

void circular_array::update_array(int size){
	vector<packet_info> db_array(size) ;
	int i = start , j = start , siz = 0 ;

	while(i < end && siz < size) {
		db_array[j] = data_array[i] ;
		i++ ;
		j++ ;
		siz ++ ;
		i %= data_array.size() ;
		j %= db_array.size() ;
	}

	data_array = db_array ;
}
