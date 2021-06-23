#ifndef WEBSERV_H
# define WEBSERV_H

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
#include "vector"
#include <sys/stat.h>

typedef struct s_response
{
	int code;
	std::string path;
	bool autoindex;
	std::vector <std::pair<int, std::string> > errPages;
	unsigned int maxBodySize;
	std::string body;
	std::string method;
	std::string defaultDir;
	std::string name;
	std::string location;
	std::string oldpath;
}				t_response;

typedef struct s_request
{
	std::string method;
	std::string path;
	std::string http;
	std::string host;
	int port;
	std::string type;
	int size;
	int code;
}				t_request;

void printResponse(t_response t);
int isWord(int i, int incr, std::string str);
int intlen(int i);
std::string intToString(int i);
#endif