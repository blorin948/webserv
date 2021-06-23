#ifndef ROUTECONF_HPP
# define ROUTECONF_HPP

#include <iostream>
#include <string>
#include "Webserv.h"
//#include "vector"
//#include "ServerConf.hpp"
class ServerConf;

class RouteConf 
{

	public :

	RouteConf();
	RouteConf(RouteConf const &c);
	RouteConf &operator=(RouteConf const &c);
	~RouteConf();
	void setRoot(std::string root);
	void setConf(std::string conf);
	void setName(std::string name);
	void setPort(std::vector <int> port);
	void setErrPages(std::vector <std::pair<int, std::string> > errPages);
	void setLimit(unsigned int sizeLimit);
	std::string getRoot(void) const;
	void printAll();
	void parseLocation();
	int getSizePath() const;
	std::string getPath(void);
	t_response getReponse(t_response res, t_request t);

	private :
	
	void setResPath(t_response &t, t_request req);
	void parseRoot(std::string root);
	void parseMethod(std::string method);
	void parsePath(void);
	void parseAutoindex(std::string autoindex);
	void parseIndex(std::string index);
	void parseRedirect(std::string redirect);
	void setResMethod(t_response &t, t_request req);
	void setResRedirect(t_response &t, t_request req);
	int _sizePath;
	std::string _path;
	unsigned int _sizeLimit;
	bool _index;
	std::vector<std::string> _method;
	std::string _rewrite;
	std::string _defaultDir;
	std::string _conf;
	std::string _servName;
	std::string _root;
	std::vector <int> _port;
	std::vector <std::pair<int, std::string> > _errPages;
	std::string _realPath;
};

std::ostream& operator<<(std::ostream& out, RouteConf const &c);

#endif