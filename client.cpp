#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include "includes/Webserv.h"
#include <arpa/inet.h>
 #include <string.h>

#define PORT 8008

std::string make_request()
{
	FILE *fp;
	std::string body;
	fp = fopen("post", "rw");
	int i = fileno(fp);
	char newstr[50000];
	read(i, newstr, 50000);
	std::string str = newstr;
	i = 0;
	i = str.find("body:");
	int tmp = i;
	if (i != std::string::npos)
	{
		i = i + 5;
		body = str.substr(i);
		str.resize(tmp);
	}
	i = 0;
	while (i < str.size() && i != std::string::npos)
	{
		i = str.find("\n", i);
		if (i != std::string::npos)
		{
			str.replace(i, 1, "\r\n");
			i = i + 3;
		}
	}
	if (body.empty() == 0)
		str.append("\r\n\r\n");
	str.append(body);
	return str;
}

int main(int argc, char const *argv[])
{
    int sock = 0; long valread;
    struct sockaddr_in serv_addr;
	std::string str = make_request();
	char hello[500];
	strcpy(hello, str.c_str());
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
    memset(&serv_addr, '0', sizeof(serv_addr));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
    
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    send(sock , hello , strlen(hello) , 0 );
	shutdown(sock, SHUT_WR);
    printf("Hello message sent\n");
    valread = read( sock , buffer, 1024);
    printf("%s\n",buffer );
    return 0;
}