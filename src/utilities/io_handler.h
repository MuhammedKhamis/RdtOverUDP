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
        static int writeData(string fileName, char *data ,int len);
        static int readData(string fileName, char *data , int len);
        static int getFileSize(string fileName);
	private:
        static bool fileExist(string fileName);
		// Disallow creating an instance of this object
		io_handler(){}
};

#endif 
