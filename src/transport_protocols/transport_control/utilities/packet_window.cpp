#include "packet_window.h"

/* constructor */
/******************************************/
packet_window::packet_window() {
    pthread_mutex_init(&lock, NULL);
}

packet_window::packet_window(int size) : packet_window() {
	this->data_array.resize(size);
	this->start = 0 ;
	this->last = 0 ;
	this->size = 0 ;
}

/* interface methods */
/******************************************/
int
packet_window::insert(struct packet_info pkt)
{
	int ret_val;

	if(is_full() == 1){
		ret_val =  -1 ;
	}else{
		data_array[last] = pkt;

		last++ ;
		size++ ;
		last %= data_array.size() ;
		ret_val = 1;
	}
	return ret_val;
}

int
packet_window::mark_acked(int seq_no)
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
packet_window::is_full()
{
    pthread_mutex_lock(&lock);
    bool ret = this->size == data_array.size();
    pthread_mutex_unlock(&lock);
	return ret ;
}

vector<packet_info>::iterator
packet_window::begin(){
	return data_array.begin() ;
}

vector<packet_info>::iterator
packet_window::end() {
	return data_array.end();
}

void packet_window::update_array(int size){


	vector<packet_info> db_array(size) ;
	int i = start , j = start , siz = 0 ;

	while(i < last && siz < size) {
		db_array[j] = data_array[i] ;
		i++ ;
		j++ ;
		siz ++ ;
		i %= data_array.size() ;
		j %= db_array.size() ;
	}

	data_array = db_array ;

}
