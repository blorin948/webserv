#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <sstream> 
#include <fstream>
#include "parsing/parsing.hpp"

#define PORT 8080


std::string&					pop(std::string& str)
{
	if (str.size())
		str.resize(str.size() - 1);
	return str;
}

std::string			nextLine(const std::string &str, size_t& i)
{
	std::string		ret;
	size_t			j;

	if (i == std::string::npos)
		return "";
	j = str.find_first_of('\n', i);
	ret = str.substr(i, j - i);
	if (ret[ret.size() - 1] == '\r')
		pop(ret);
	i = (j == std::string::npos ? j : j + 1);
	return ret;
}

std::string request(std::string file)
{
	std::string buf;
	std::ostringstream buff;
   std::string hello = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: ";
	std::ifstream myfile(file);
	while (getline(myfile, buf))
		buff << buf;
	buf = buff.str();
//	if (myfile.is_open())
//		std::cout << buf << "dsjfhsihdsifbghi" <<std::endl;
	hello = hello + std::to_string(buf.length()) + "\n\n";
    hello = hello + buf;
	return (hello);
}

std::vector<std::string> samerelapute(std::string buffer)
{
	std::vector<std::string> ok;
	size_t i = 0;
	int a = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
		{
			buffer[i] = '\0';
			ok.push_back(nextLine(buffer, i));
			a = 0;
		}
		a++;
		i++;
	}
	return (ok);
}

int main(int argc, char const *argv[])
{
    int server_fd, new_socket; long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    std::ofstream output1("dsa", std::ifstream::in);
	
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 10) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }
	std::string hello;
	std::string buffstr;
	int i = 0;
	char *str;
    while(1)
    {
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }
        char buffer[30000] = {0};
        valread = read(new_socket , &buffer, 700);
		buffstr = buffer;
	std::vector<std::string> ok=samerelapute(buffstr);
	std::vector<std::string>::iterator it = ok.begin();
	while (it != ok.end())
		std::cout<<"la = |" << *it++ << "|\n";
		
		hello.erase();
	//	parsing parse(buffstr);
		std::cout << buffstr << std::endl;
		if (buffstr.find("/chat.ogg") != std::string::npos)
		{
			//std::cout << "heyDFJHGBFDKDFGKBHDFK\n";
			hello = request("chat.ogg");

			//std::cout << hello << std::endl;
			write(new_socket, hello.c_str(), strlen(hello.c_str()));
			//printf("------------------Hello message sent-------------------\n");
		}
		else if (buffstr.find("/index.html") != std::string::npos)
		{	
			hello = request("index.html");
			//std::cout << hello << std::endl;
			write(new_socket, hello.c_str(), strlen(hello.c_str()));
			//printf("------------------Hello message sent-------------------\n");
		}                                                                                                               
    close(new_socket);
    }
    return 0;
}