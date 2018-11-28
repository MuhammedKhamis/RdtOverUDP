#include "connection_handler.h"

/* constructor */
/******************************************/

/* interface methods */
/******************************************/
void
connection_handler::handle_client()
{
	// 01. read file from disk

	// 02. disassemble file into packets

	// 03. implement RDT strategy
	rdt_strategy *strategy = new stop_and_wait();
	rdt_strategy *strategy = new selective_repeat();
	strategy.implement();
}