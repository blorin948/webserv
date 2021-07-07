#ifndef SERVERCONF_HPP
# define SERVERCONF_HPP

#include <iostream>
#include <string>
#include "Webserv.h"
#include "RouteConf.hpp"

class ServerConf
{

	public :

	class ParseErrorException : public std::exception
	{
		virtual const char *what() const throw();
	};

	ServerConf(std::string &conf);
	ServerConf();
	ServerConf(ServerConf const &c);
	ServerConf &operator=(ServerConf const &c);
	~ServerConf();
	void parseRoute();
	unsigned int getLimit() const;
	std::string getConfFile() const;
	std::string getRoot() const;
	std::string getName() const;
	std::vector <int> getPort() const;
	std::vector <std::pair<int, std::string> > getErrPages() const;
	void copyRoute(RouteConf *x, int i);
	t_response getReponse(t_response res, t_request req);
	void printAll(void);
	void setDefault(bool defaulte);
	void set_can_accept_connection(bool accept);
	bool get_can_accept_connection(void);
	RouteConf *getCurrentRoute(t_request req) const;
	bool isRoute(t_request req) const;

	private :

	t_response response_from_server(t_response res, t_request req);
	void orderRoute();
	void tri_bulle();
	void parseAll();
	void splitConfRoute(std::string location);
	void parseRoot(std::string root);
	void parseName(std::string name);
	void parsePort(std::string listen);
	void parseSize(std::string size);
	void parseError(std::string error);
	int cut_conf(std::string conf, int &a, int &length);
	int routeLength(int i);


	bool _errorParsing;
	bool _default;
	bool _can_upload;
	bool _can_accept;
	int _i;
	unsigned int _sizeLimit;
	std::string _conf;
	std::string _servName;
	std::string _root;
	std::vector <int> _port;
	std::vector <std::pair<int, std::string> > _errPages;
	std::vector <RouteConf*> _route;
	std::vector<std::string> _confRouteOnly;
};

#endif