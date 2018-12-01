#include <io_handler.h>
#include <packet.h>
#include <packet_manager.h>
#include "connection_handler.h"

/* constructor */
/******************************************/

connection_handler::connection_handler(struct sockaddr_in client, char* file_name) :
		curr_client(client), file_name(file_name) {
	//choose the strategy
	strategy = new stop_and_wait(curr_client);
}
/* interface methods */
/******************************************/
void
connection_handler::handle_client()
{
    vector<string> file_lines;

	// 01. read file from disk
	io_handler::read_file(file_name, &file_lines);

	// 02. disassemble file into packets
    vector<packet> file_packets;
    for(string file_line: file_lines){
        vector<packet> line_packets = packet_manager::disassemble_data(file_line.data());
        file_packets.insert(file_packets.end(), line_packets.begin(), line_packets.end());
    }

    // 03. implement RDT strategy
	strategy->implement(&file_packets);

}