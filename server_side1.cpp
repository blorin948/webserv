#include "Webserv.h"
#define PORT 8000
#include "ErrorIndex.hpp"
#include "GetResponse.hpp"
/*
std::string request(std::string file)
{
	int i;
	std::string buf;
	std::ostringstream buff;
   std::string hello = "HTTP/1.1 200 OK\nContent-Type: video/mp4\nContent-Length: ";
	std::ifstream myfile(file.c_str(), std::ifstream::in);
	while (getline(myfile, buf))
		buff << buf;
	buf = buff.str();
//	if (myfile.is_open())
i = buf.length();
std::stringstream ss;
ss << i;
std::string intstring = ss.str();
	hello = hello + intstring + "\n\n";
    hello = hello + buf;
	return (hello);
}*/

std::vector<std::string> samerelapute(std::string buffer)
{
	std::vector<std::string> ok;
	char	*str = new char [buffer.length() + 1];
	strcpy (str, buffer.c_str());
	size_t a = 0;
	size_t i = 0;/*
	for (int o = 0; o < buffer.length(); i++)
	{
		if (str[i] == '\n')
		{
			buffer[i] = '\0';
			ok.push_back(buffer.substr(a));
			a = o + 1;
		}
		o++;
	}*/
	while (str[i])
	{
		if (str[i] == '\n')
		{
			str[i] = '\0';
			ok.push_back(str + a);
			a = i + 1;
		}
		i++;
	}
	return (ok);
}

void do_get(std::vector<std::string >request, std::string &serv_response)
{
	GetResponse ok(request);
	ErrorIndex t;
	int code = 0;
	code = ok.openFile();
	if (code)
	{
		serv_response = t.getPage(code);
	}
	else
		serv_response = ok.setAll();
}

void find_request(std::vector<std::string >vec, std::string &response)
{
	int i = 0;
	if (vec[0].find("GET") == 0)
	{
		do_get(vec, response);
	}
	//std::cout << i << std::endl;
}

std::string create_post(void)
{
	std::string post;
	post.append("POST /index_example.html HTTP/1.1\nContent-type: text/html\nContent-length: 16\n\n<p>New File</p>");
	return (post);
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
		std::vector<std::string> ok = samerelapute(buffstr);
		std::vector<std::string>::iterator it = ok.begin();
		std::cout.flush();
		/*while (it != ok.end())
		{
			std::cout<<"La = |" << *it << "|" << std::endl;
			*it++;
		}*/
		std::cout << "true one = \n" << buffstr << std::endl;
		hello.erase();
		find_request(ok, hello);
		std::cout <<" reponse = " <<  hello << std::endl;
		//std::cout << buffstr << std::endl;
	/*	if (buffstr.find("/video.mp4") != std::string::npos)
			hello = request("video.mp4");
		else if (buffstr.find("/index.html") != std::string::npos)
			hello = request("index.html");*/
		write(new_socket, hello.c_str(), strlen(hello.c_str()));                                                                                                            
    	close(new_socket);
		hello.erase();
    }
    return 0;	
}
