#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <sstream> 
#include <fstream>
//#include "parsing/parsing.hpp"
#include <utility> 
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include "vector"


int main()
{
	struct stat s;
	stat("ww", &s);
	bool ok;
	ok = S_ISDIR(s.st_mode);
	if (ok == true)
		std::cout <<"dir" << std::endl;
	
	std::ostringstream buf;
	std::string file;
	std::ifstream myfile("www", std::ifstream::in);
	if (!(myfile.is_open()))
		std::cout << "pas ouvert" << std::endl;
	while (getline(myfile, file))
		buf << file;
	file = buf.str();
	std::cout << file << std::endl;
	return (200);
}