#ifndef GETRESPONSE_HPP
# define GETRESPONSE_HPP

#include <iostream>
#include <string>
#include "Webserv.h"

class GetResponse
{

	public :

	GetResponse(std::vector<std::string> request);
	void setLength();
	void setType();
	void setCode();
	void setName();
	std::string setAll();
	std::string getErrorPage(std::string name, std::string code);
	GetResponse();
	GetResponse(GetResponse const &c);
	GetResponse &operator=(GetResponse const &c);
	~GetResponse();
	int openFile();
	int openFile(std::string name);
	private :


	int getName();
	std::vector<std::string> _request;
	std::vector<std::string> _response;
	std::string _code;
	std::string _type;
	std::string _length;
	std::string _body;
	std::string _name;
	std::string _file;

};

#endif