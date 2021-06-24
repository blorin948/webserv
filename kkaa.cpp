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
	std::string t("POST /upload HTTP/1.1Host: localhost:8005User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.14; rv:86.0) Gecko/20100101 Firefox/86.0Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8Accept-Language: fr,fr-FR;q=0.8,en-US;q=0.5,en;q=0.3Accept-Encoding: gzip, deflateContent-Type: multipart/form-data; boundary=---------------------------117315503721977773842820609451Content-Length: 1673Origin: http://localhost:8005Connection: keep-aliveReferer: http://localhost:8005/upload.htmlUpgrade-Insecure-Requests: ");
	std::cout << t.length() << std::endl;
	
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