#include "io_handler.h"

/* interface functions */
/******************************************/
void
io_handler::read_file(char file_dir[], vector<string> *file_buffer)
{
	ifstream file(file_dir);
	if (file.is_open()) {
		string line;
		while (getline(file, line))
		{
			file_buffer->push_back(string(line));
		}
		file.close();
	}
}