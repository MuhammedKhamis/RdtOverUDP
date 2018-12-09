#include "sr_server.h"

/* constructor */
/******************************************/
sr_server::sr_server(port_handler *p) : selective_repeat(p) {}

/* interface method */
/******************************************/

void sr_server::init(vector<data_packet*> &data_packets) {
    p_window = packet_window(INIT_WIN_LEN);
    this->data_packets = data_packets;
    ack_packet ak(data_packets.size());
    p_handler->send(ak.to_string());
}

/* interface method */
/******************************************/
void
sr_server::implement()
{
    int sent_pkts_counter = 0; // how many packets are sent
    int ack_pkts_counter = 0; // how many packets are acked

    // 01. send initial N packets
    while(sent_pkts_counter < INIT_WIN_LEN)
    {
        send_packet(sent_pkts_counter);

        sent_pkts_counter++;
        if(sent_pkts_counter >= data_packets.size())
        {
            implementation_done_flag = 1; // to exit timer thread
            return;
        }
    }

    // 02. run Timer thread
    pthread_create(&time_handler_id, NULL, run_timer_thread, this);

    // 03. wait for acknowledgements
    while(ack_pkts_counter < data_packets.size())
    {
        // wait for ack
        string buffer;
        p_handler->receive(buffer); // blocked receive
        ack_packet *packet = packet_parser::create_ackpacket(buffer);

        // update window
        int remaining_window = p_window.mark_acked(packet->get_seqno());
        // send new open space
        while(remaining_window > 0)
        {
            send_packet(sent_pkts_counter);
            remaining_window--;
            sent_pkts_counter++;
            if(sent_pkts_counter >= data_packets.size())
            {
                implementation_done_flag = 1; // to exit timer thread
                return;
            }
        }
    }

    // 04. implementation done
    implementation_done_flag = 1; // to exit timer thread

}


/* utility method */
/******************************************/
void
sr_server::send_packet(int seq_no)
{
    // get packet by seq_no
    data_packet *curr_pkt = data_packets.at(seq_no);
    // send packet to client
    p_handler->send(curr_pkt->to_string());
    // create new entry
    struct packet_info tmp;
    tmp.seq_no = curr_pkt->get_seqno();
    tmp.acked = 0;
    time(&tmp.start_time);
    // insert into window
    p_window.insert(tmp);
}


/* TIMER methods */
/******************************************/
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
            if(difftime(curr_time, ptr->start_time) < PKT_LOSS_TIMEOUT){continue;} // NOT timed-out --> skip
            // handle timed-out packet
            p_handler->send(data_packets.at(ptr->seq_no)->to_string()); // resend packet
            time(&ptr->start_time); // reset timer
        }
    }
}