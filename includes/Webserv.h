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
#include <sys/poll.h>
#include <sys/wait.h>
#include <errno.h>
#include <netinet/in.h>
#include <map>
#define TRUE             1
#define FALSE            0
#define MAX_CONNECTION 500

typedef struct s_response
{
	int code;
	std::string path;
	bool autoindex;
	bool can_upload;
	std::map <int, std::string> errPages;
	unsigned int maxBodySize;
	std::string body;
	std::string method;
	std::string defaultDir;
	std::string name;
	std::string location;
	std::string oldpath;
	std::string uploadPath;
	std::string cgiResponse;
	std::string type;
}				t_response;

typedef struct s_request
{
	std::string method;
	std::string path;
	std::string http;
	std::string body;
	std::string host;
	int port;
	std::string type;
	unsigned long size;
	bool isUpload;
	std::string uploadName;
	int code;
}				t_request;

typedef struct s_socket
{
	int port;
	int socket;
	struct sockaddr_in address;
	int addrlen;

}t_socket;

class ServerConf;

void printResponse(t_response t);
int isWord(int i, int incr, std::string str);
int intlen(int i);
std::string intToString(int i);
void initResponse(t_response &t);
void initRequest(t_request &t);
void printAllRequest(t_request t);
bool IsPathExist(const std::string &s);
char *newStr(std::string source);
void do_get(t_response t, std::string &serv_response);
void do_post(t_response &res, t_request req,  std::string &serv_response, ServerConf *serv);
void do_cgi(t_response &res, std::string &serv_response);
void do_delete(t_response &res, std::string &serv_response);
void reset_connection(std::vector<ServerConf*> serv);
struct pollfd create_socket(int port, t_socket *t);
std::vector<ServerConf *> create_server(char *conf);
t_response parse_response(std::vector<ServerConf*> serv, int i, t_request req);
t_request parse_request(std::string buffer);
void check_bracer(char *str2);
#endif