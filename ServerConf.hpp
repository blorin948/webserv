#ifndef SERVERCONF_HPP
# define SERVERCONF_HPP

#include <iostream>
#include <string>
#include "Webserv.h"

class ServerConf
{

	public :

	ServerConf(std::string &conf);
	ServerConf();
	ServerConf(ServerConf const &c);
	ServerConf &operator=(ServerConf const &c);
	~ServerConf();

	private :

	void parseAll();
	void parsePort();
	int cut_conf(std::string conf, int &a, int &length);
	std::string _conf;
	bool _errorParsing;
	std::vector <int> _port;
	std::string _servName;
	bool _default;
	std::string _root;
	std::pair<int, std::string> _errPages;
	unsigned int _sizeLimit;
};

#endif