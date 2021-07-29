#ifndef GETRESPONSE_HPP
# define GETRESPONSE_HPP

#include <iostream>
#include <string>
#include "Webserv.h"
#include "AutoIndexGenerator.hpp"

class GetResponse
{

	public :

	GetResponse();
	void setLength();
	void setType();
	void setCode();
	void setName();
	std::string setAllCgi(t_response res);
	std::string setAll(int code);
	std::string getErrorPage(t_response res);
	GetResponse(GetResponse const &c);
	~GetResponse();
	int openFile();
	bool isDirectory(std::string path);
	int openFile(std::string name);
	std::string getFullResponse(t_response);
	std::string redirectPage(t_response res);
	std::string handle_dir(t_response res);
	void modifyIfDir(t_response &t);
	int isDir(t_response t);
	private :


	int getName();
	t_response _res;
	std::vector<std::string> _request;
	std::vector<std::string> _response;
	std::string _code;
	std::string _type;
	std::string _defaultError;
	std::string _length;
	std::string _body;
	std::string _name;
	std::string _file;

};

#endif