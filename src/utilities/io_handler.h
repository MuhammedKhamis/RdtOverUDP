#ifndef IO_HANDLER_H
#define IO_HANDLER_H

/* import libraries */
/******************************************/
#include <fstream> // read write file
#include <iostream> // read write screen
#include <vector>
#include <string>
using namespace std;

/* class definition */
/******************************************/
class io_handler
{
	public:
		static void read_file(string file_dir, vector<string> &file_buffer);
		static void write_file(string file_dir, vector<string> &file_buffer);

	private:
		// Disallow creating an instance of this object
		io_handler(){}
};

#endif 
