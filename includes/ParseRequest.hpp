#ifndef PARSEREQUEST_HPP
# define PARSEREQUEST_HPP

#include <iostream>
#include <string>
#include "Webserv.h"

class ParseRequest
{

	public :

	ParseRequest();
	ParseRequest(ParseRequest const &c);
	~ParseRequest();
	void parseMethod(void);
	void parsePath(void);
	void parseHttp(void);
	void parseBodyUpload(void);
	void parseBody(void);
	void parseHost(std::string host);
	void getRequest(t_request &t, std::vector<std::string> req);
	void printAll(t_request t);
	void parseType(std::string type);

	private :
	int getBodyLength(void);
	std::vector <std::string> _request;
	std::string _method;
	std::string _body;
	std::string _path;
	std::string _http;
	std::string _host;
	int _port;
	std::string _type;
	int _size;
	unsigned long _i;
	int _code;
	bool _isUpload;
	std::string _boundary;
	std::string _uploadName;

};

#endif