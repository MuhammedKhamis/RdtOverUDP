#include "sr_server.h"

/* constructor */
/******************************************/
sr_server::sr_server(struct sockaddr_in client, int socket_fd, socklen_t client_len)
        : selective_repeat(client,socket_fd, client_len){

    this->con_controller();
	window_size = 1;
	this->p_window(1);
}

/* interface method */
/******************************************/
void
init(vector<data_packet> *packets)
{
	this->packets = packets;
}


/* interface method */
/******************************************/
void
sr_server::implement()
{
	int sent_counter = 0; // how many packets are sent
	int ack_counter = 0; // how many packets are acked
	// 01. send initial N packets
	while(sent_counter < window_size)
	{
		send_packet(sent_counter);
		sent_counter++;
	}

	// 02. run Timer thread
	pthread_create(&timer_handler, run_timer_handler, NULL, this);

	// 02. wait for acknowledgements
	while(ack_counter < packets->length())
	{
		// wait for ack
		char *buffer;
		p_handler.receive(buffer); // blocked receive
		ack_packet packet = packet_parser::parse_ack_packet(buffer);

		// update window
		int remaining_window = p_window.mark_acked(packet.get_seq_no());
		// send new open space
		while(remaining_window > 0)
		{
			send_packet(sent_counter);
			sent_counter++;
			remaining_window--;
		}
	}

}


/* interface method */
/******************************************/
void
sr_server::send_packet(int index)
{
	data_packet curr_pkt = packets->at(index);
	// send packet to client
	p_handler.send(curr_pkt.to_string());
	// create new entry in 
	struct packet_info tmp;
	tmp.seq_no = curr_pkt.seq_no;
	tmp.acked = 0;
	time(&tmp.start_time);
	// insert into window
	p_window.insert(tmp);
}

void*
sr_server::run_timer_thread(void *tmp)
{
	((sr_server*) tmp)->timer_handler();
}

void
sr_server::timer_handler()
{
	time_t curr_time;
	while(implementation_done_flag == 0)
	{
		vector<struct packet_info>::iterator ptr;
	    for (ptr = p_window.begin(); ptr < p_window.end(); ptr++) 
	    {
	    	if(ptr->acked == 1){continue;} // acked pkt -> skip
	    	time(&curr_time); // get system current time
	    	if(difftime(curr_time, ptr->start_time) < TIMEOUT){continue;} // NOT timed-out --> skip
	    	// handle timed-out packet
	    	p_handler.send(packets->at(ptr->seq_no).to_string()); // resend packet
	    	time(&ptr->start_time); // reset timer
	    }
	}
}