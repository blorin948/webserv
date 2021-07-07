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
#include <poll.h>
#include <sys/select.h>

#define PORT 8080
#define SERVER_PORT  12345

#define TRUE             1
#define FALSE            0

SERVER_SOFTWARE ; Webserv/1.0
SERVER_NAME = nom du SERVEr;
GATEWAY_INTERFACE = CGI/1.1
SERVER_PROTOCOL = HTTP/1.1
SERVER_PORT = port;
REQUEST_METHOD  = method
PATH_INFO = chemin complet ex = www/test/as au lieu de test/as;
SCRIPT_NAME = path vers le script;
QUERY_STRING = tout apres le ? dans l4url, rien si pos;
REMOTE_HOST = nom du server;
REMOTE_ADDR = adresse ip de requete;
CONTENT_LENGTH = taille du query ou body;
CONTENT_TYPE = Content-Type: text/html

