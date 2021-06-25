#include "Webserv.h"
#define PORT 8005
#include "ErrorIndex.hpp"
#include "GetResponse.hpp"
#include "ParseRequest.hpp"
#include "ServerConf.hpp"
#include "PostResponse.hpp"

void initResponse(t_response &t)
{
	t.code = 0;
	t.autoindex = false;
}

void initRequest(t_request &t)
{
	t.size = 0;
	t.port = 0;
	t.code = 0;
	t.isUpload = false;
}

std::vector<std::string> samerelapute(std::string buffer)
{
	std::vector<std::string> ok;
	char	*str = new char [buffer.length() + 1];
	strcpy (str, buffer.c_str());
	size_t a = 0;
	size_t i = 0;
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

void do_get(t_response t, std::string &serv_response)
{
	GetResponse ok;
	serv_response = ok.getFullResponse(t);
}

void do_post(t_response &res, t_request req,  std::string &serv_response, ServerConf *serv)
{
	PostResponse ok;
	std::cout << "req size = " << req.size << " seerv limit = " << serv->getLimit() <<std::endl;
	if (req.size > serv->getLimit())
		res.code = 413;
	serv_response = ok.makePost(req, res);
}

void find_request(t_response t, t_request req, std::string &response, ServerConf *serv)
{
	int i = 0;
	if (t.method.compare("GET") == 0)
	{
		do_get(t, response);
	}
	if (t.method.compare("POST") == 0)
	{
		do_post(t, req, response, serv);
	}
	//std::cout << i << std::endl;
}

std::string create_post(void)
{
	std::string post;
	post.append("POST /index_example.html HTTP/1.1\nContent-type: text/html\nContent-length: 16\n\n<p>New File</p>");
	return (post);
}

ServerConf openT()
{
	std::ostringstream buf;
	std::string file;
	std::ifstream myfile("test.conf", std::ifstream::in);
	/*if (!(myfile.is_open()))
		return NULL;*/
	while (getline(myfile, file))
	{
		buf << file;
		buf << "\n";
	}
	file = buf.str();
	try
	{
		ServerConf t(file);
		return (t);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}


int main(int argc, char const *argv[])
{
    int server_fd, new_socket; long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
	ServerConf serv = openT();
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
        char buffer[300000] = {0};
        valread = read(new_socket , &buffer, 300000);
		buffstr = buffer;
		//std::cout << "true one = \n" << buffer << std::endl;
		std::vector<std::string> ok = samerelapute(buffstr);
		std::vector<std::string>::iterator it = ok.begin();
		/*while (it != ok.end())
		{
			std::cout << *it++ << std::endl;
		}*/
		ParseRequest t(ok);
		t_request req;
		initRequest(req);
		t.getRequest(req);
		//t.printAll(req);
		t_response res;

		initResponse(res);
		res = serv.getReponse(res, req);
		//printResponse(res);
		//std::cout.flush();
		hello.erase();
		std::cout << "SERVEER SIZE = " << serv.getLimit() << std::endl;
		find_request(res, req,  hello, &serv);
		//std::cout <<" reponse = " <<  hello << std::endl;
		write(new_socket, hello.c_str(), strlen(hello.c_str()));                                                                                                            
    	close(new_socket);
		hello.erase();
    }
    return 0;	
}
