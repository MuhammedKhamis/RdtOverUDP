#include "packet_window.h"

/* constructor */
/******************************************/
circular_array::circular_array() {

}

circular_array::circular_array(int size)
{
	this->data_array.resize(size,{1,1,1});
	this->start = 0 ;
	this->last = 0 ;
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
	data_array[last] = pkt;

	this->last++ ;
	this->size++ ;
	this->last %= data_array.size() ;

	return 1;
}

int
circular_array::mark_acked(int seq_no)
{
	int index = (start + seq_no - data_array[start].seq_no)  % data_array.size() ;
	int total_ack = 0 ;

	data_array[index].acked = true ;

	if(index == start) {
		while(data_array[index].acked and index != last){
			index += 1 ;
			index %= data_array.size() ;
			total_ack ++ ;
		}
		this->start = index ;
		this->size -= total_ack ;
	}

	return total_ack ;
}

bool
circular_array::is_full()
{
	return this->size == data_array.size() ;
}

vector<packet_info>::iterator
circular_array::begin(){
	return data_array.begin() ;
}

vector<packet_info>::iterator
circular_array::end() {
	return data_array.end();
}

void circular_array::update_array(int size){
	vector<packet_info> db_array(size) ;
	int i = start , j = 0 , siz = 0 ;

	while(i != last && siz < size) {
		db_array[j] = data_array[i] ;
		i++ ;
		j++ ;
		siz ++ ;
		i %= data_array.size() ;
	}

	data_array = db_array ;
	start = 0 ;
	last = j ;
	size = j ;

}

packet_info circular_array::get_index(int seq_no) {
	int index = (start + seq_no - data_array[start].seq_no)  % data_array.size() ;
	return data_array[index] ;
}
