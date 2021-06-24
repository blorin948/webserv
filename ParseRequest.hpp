#ifndef PARSEREQUEST_HPP
# define PARSEREQUEST_HPP

#include <iostream>
#include <string>
#include "Webserv.h"

class ParseRequest
{

	public :

	ParseRequest(std::vector <std::string> request);
	ParseRequest();
	ParseRequest(ParseRequest const &c);
	ParseRequest &operator=(ParseRequest const &c);
	~ParseRequest();
	void parseMethod(void);
	void parsePath(void);
	void parseHttp(void);
	void parseBody(void);
	void parseHost(std::string host);
	void getRequest(t_request &t);
	void printAll(t_request t);
	void parseType(std::string type);

	private :
	std::vector <std::string> _request;
	std::string _method;
	std::vector <std::string> _body;
	std::string _path;
	std::string _http;
	std::string _host;
	int _port;
	std::string _type;
	int _size;
	int _i;
	int _code;
	bool _isUpload;

};

#endif