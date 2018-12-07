#include "io_handler.h"
#include <sys/stat.h>

/* interface functions */
/******************************************/
bool io_handler::fileExist(string fileName) {
	struct stat buffer;
	return (stat (fileName.c_str(), &buffer) == 0);
}

int io_handler::getFileSize(string fileName) {
	if(fileExist(fileName)){
		ifstream in(fileName.c_str(), ifstream::ate | ifstream::binary);
		int len = in.tellg();
		in.close();
		return len;
	}
	return -1;
}

int io_handler::readData(string fileName, char *data, int len) {
	if(fileExist(fileName)){

		FILE* fp = fopen(fileName.c_str(),"rb");
		int sz = len;
		while(len > 0) {
			int read = fread(data, 1, len, fp);
			if(read == -1){
				return -1;
			}
			if(read == 0){
				break;
			}
			len-=read;
			data+=read;
		}
		fclose(fp);
		return sz - len ;
	}
	return -1;
}
int io_handler::writeData(string fileName, char *data, int len) {

	FILE* fp = fopen(fileName.c_str(),"wb+");
	int sz = len;
	while (len > 0) {
		int written = fwrite(data, 1, len, fp);
		if(written == -1){
			return -1;
		}
		if(written == 0){
			break;
		}
		len -= written;
		data += written;

	}
	fclose(fp);
	return sz - len;
}