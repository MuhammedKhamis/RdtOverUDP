#ifndef TEXT_HANDLER_H
#define TEXT_HANDLER_H

/* import libraries */
/******************************************/
#include <vector>
#include <string>
#include <cstring>
#include <bits/stdc++.h>

using namespace std;


/* class definition */
/******************************************/
class text_handler
{
	public:
		// interface methods
		static vector<string> divide_data_size(string data, int size);
		static vector<string> tokenize(string s, string delimiter);

	private:
		// prevent instance
		text_handler();
};

#endif 

