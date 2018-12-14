#include "text_handler.h"

vector<string> text_handler::tokenize(string s, string delimiter) {
    vector<string> tokens ;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        tokens.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s) ;
    return tokens ;

}

vector<string> text_handler::divide_data_size(string data, int size = 500) {
    vector<string> data_divide;
    for(int i = 0 ; i < data.size() ; i += size){
        string chunk = data.substr(i, size) ;
        data_divide.push_back(chunk) ;
    }

    return data_divide ;
}