#include "packet_parser.h"

#define LSH_TOK_DELIM " \t\r\n();" // delimiter used in string tokenization

/* tokenization function */
/******************************************/
void
packet_parser::tokenize(string target_line, vector<string> *result_tokens)
{
	// abide by the interface
	char line[target_line.length()];
	strcpy(line, target_line.c_str());

	// actual tokenize
    char *token;
    token = strtok(line, LSH_TOK_DELIM);
    while (token != NULL)
    {
      result_tokens->push_back(string(token));
      token = strtok(NULL, LSH_TOK_DELIM);
    }
}

/* interface methods */
/******************************************/