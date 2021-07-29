#include "includes/Webserv.h"
#include "includes/GetResponse.hpp"
#include "includes/ParseRequest.hpp"
#include "includes/PostResponse.hpp"
#include "includes/CgiMaker.hpp"
#include "includes/DeleteRequest.hpp"
#include "includes/ServerConf.hpp"

std::vector<std::string> split_request(std::string buffer)
{
	std::vector<std::string> ok;
	size_t i = 0;
	std::string tmp;
	std::string body;
	i = buffer.find("\r\n\r\n");
	if (i != std::string::npos)
	{
		body = buffer.substr(i + 4);
		buffer.resize(i);
	}
	i = 0;
	while (i < buffer.size() && i != std::string::npos)
	{
		if (i != std::string::npos)
		{
			tmp.clear();
			while (i < buffer.size() && buffer[i] != '\r')
			{
				tmp.append(1, buffer[i]);
				i++;
			}
			ok.push_back(tmp);
		}
		i = i + 2;
	}
	i = 0;
	ok.push_back(body);
	return (ok);
}

void check_bracer(char *str2)
{
	std::ostringstream buf;
	std::string file;
	std::ifstream myfile(str2, std::ifstream::in);
	int open = 0;
	int closed = 0;
	unsigned long i = 0;	
	if (!(myfile.is_open()))
		throw std::runtime_error("Error while opening conf file");
	while (getline(myfile, file))
	{
		buf << file;
		buf << "\n";
	}
	file = buf.str();
	while ((i = file.find("{", i)) != std::string::npos)
	{
		open++;
		i++;
	}
	i = 0;
	while ((i = file.find("}", i)) != std::string::npos)
	{
		closed++;
		i++;
	}
	if (open != closed)
		throw std::runtime_error("Error with bracers");
}

t_request parse_request(std::string buffer)
{
	t_request req;
	std::vector<std::string> requestTab = split_request(buffer);
	ParseRequest request;
	request.getRequest(req, requestTab);
	return (req);
}

t_response parse_response(std::vector<ServerConf*> serv, int i, t_request req)
{
	t_response res;
	CgiMaker cgi;
	initResponse(res);
	if (serv[i]->isRoute(req) && (serv[i]->getCurrentRoute(req)->getIsCgi() == true) && cgi.is_cgi(req, serv[i]->getCurrentRoute(req)))
	{
		res.errPages = serv[i]->getErrPages();
		res = cgi.make_cgi(res, req, serv[i]->getCurrentRoute(req));
		res.cgiResponse = cgi.getBuffer();
		return res;
	}
	res = serv[i]->getReponse(res, req);
	return res;
}

std::vector<ServerConf *> create_server(char *conf)
{
	std::ostringstream buf;
	std::string file;
	std::ifstream myfile(conf, std::ifstream::in);
	std::vector<ServerConf *> serv;
	if (!(myfile.is_open()))
	{
		std::cout << "Error while opening conf file" << std::endl;
		return serv;
	}
	while (getline(myfile, file))
	{
		buf << file;
		buf << "\n";
	}
	file = buf.str();
	while (file.find("server") != std::string::npos)
	{
		ServerConf *t = new ServerConf(file);
		if (serv.size() == 0)
			t->setDefault(true);
		serv.push_back(t);
	}
	return (serv);
}
