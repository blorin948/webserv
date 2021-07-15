#ifndef CGIMAKER_HPP
# define CGIMAKER_HPP

#include <iostream>
#include <string>
#include "Webserv.h"
#include "RouteConf.hpp"
#include <map>

class CgiMaker
{

	public :

	CgiMaker();
	CgiMaker(CgiMaker const &c);
	CgiMaker &operator=(CgiMaker const &c);
	~CgiMaker();
	int isCgiFile(t_request req, RouteConf* route);
	t_response make_cgi(t_response res, t_request req, RouteConf* route);
	int is_cgi(t_request req, RouteConf* route);
	void set_path(t_request req);
	std::string getBuffer(void) const;
	t_response parseCgi(t_response res);

	private :

	int parseCode(std::string status);
	std::string parseType(std::string type);
	std::string parseBody(void);
	int execute_cgi(t_request req, RouteConf *route);
	void setQuery(t_request req);
	void create_env(t_request req, RouteConf *route);
	char **mapToChar(std::map<std::string, std::string> env);
	std::map<std::string, std::string> _env;
	std::string _full_path;
	std::string _body;
	std::string _query;
	std::string _length;
	std::string _path_WO_query;
	std::string _buffer;
};

#endif