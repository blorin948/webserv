#ifndef ROUTECONF_HPP
# define ROUTECONF_HPP

#include <iostream>
#include <string>
#include "Webserv.h"

class RouteConf : public ServerConf
{

	public :

	RouteConf();
	RouteConf(RouteConf const &c);
	RouteConf &operator=(RouteConf const &c);
	~RouteConf();

	private :

	std::vector<std::string> _method;
	std::vector<std::string> _rewrite;
	bool index;
	std::string default_dir;
};

#endif