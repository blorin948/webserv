#include "ServerConf.hpp"

ServerConf::ServerConf(std::string &conf) : _errorParsing(false), _sizeLimit(0)
{
	int start = 0;
	int length = 0;
	int end = cut_conf(conf, start, length);
	_conf = conf.substr(start, length);
	start = conf.find("server");
	conf.erase(0, end + start);
	splitConfRoute("location");
	parseAll();
}

void ServerConf::splitConfRoute(std::string location)
{
	int start = 0;
	int length = 0;
	int end = 0;
	int i = 0;
	std::string route;
	while ((i = _conf.find(location, i)) && i != std::string::npos)
	{
		if (isWord(i, location.length()))
		{
			i = i + location.length();
			length = routeLength(i);
			if (length == 0)
				throw "Error with location block";
			route = _conf.substr(i, length);
			_confRouteOnly.push_back(route);
			route.clear();
			_conf.erase(i - location.length(), length + location.length());
			i = 0;
		}
		i++;
	}
}

int ServerConf::routeLength(int i)
{
	int length = i;
	int col = 0;
	i = _conf.find("{", i);
	if (i == std::string::npos)
		return (0);
	i++;
	col++;
	while (_conf[i] && col > 0)
	{
		if (_conf[i] == '{')
			col++;
		if (_conf[i] == '}')
			col--;
		i++;
	}
	length = i - length;
	if (_conf[i] == '}')
		i++;
	if (col > 0)
		return (0);
	return (length);

}

void ServerConf::parseAll(void)
{
	parsePort("listen");
	parseName("server_name");
	parseRoot("root");
	parseSize("client_max_body_size");
	parseError("default_error");
	parseRoute();
}

void ServerConf::copyRoute(RouteConf *x, int i)
{
	x->setRoot(getRoot());
	x->setConf(_confRouteOnly[i]);
	x->setName(getName());
	x->setPort(getPort());
	x->setErrPages(getErrPages());
	x->setLimit(getLimit());
}

void ServerConf::parseRoute(void)
{
	int nbRoute = _confRouteOnly.size();
	int i = 0;
	while (i < nbRoute)
	{
		RouteConf *x = new RouteConf;
		copyRoute(x, i);
		_route.push_back(x);
		_route[i]->printAll();
		i++;
	}

}

ServerConf::ServerConf(void)
{

}

ServerConf::ServerConf(ServerConf const &c)
{
	*this = c;
}


const char *ServerConf::ParseErrorException::what() const throw()
{
	return ("No port on conf file");
}


ServerConf &ServerConf::operator=(ServerConf const &c)
{
	return (*this);
}

ServerConf::~ServerConf()
{
	_conf.clear();
	_servName.clear();
	_root.clear();
	_port.clear();
	_errPages.clear();
}

///////////////////////////////////////////////////////////////
/////////////// GET FONCTIONS /////////////////////////////////

unsigned int ServerConf::getLimit() const
{
	return (_sizeLimit);
}

std::string ServerConf::getConfFile() const
{
	return (_conf);
}

std::string ServerConf::getRoot() const
{
	return (_root);
}

std::string ServerConf::getName() const
{
	return (_servName);
}

std::vector <int> ServerConf::getPort() const
{
	return (_port);
}

std::vector <std::pair<int, std::string> > ServerConf::getErrPages() const
{
	return (_errPages);
}
///////////////////////////////////////////////////////////////
/////////////// PARSING FONCTIONS /////////////////////////////

void ServerConf::parseError(std::string error)
{
	int i = 0;
	int first = 0;
	std::string second;
	while ((i = _conf.find(error, i)) && i != std::string::npos)
	{
		if (isWord(i, error.length()))
		{
			first = (atoi((_conf.c_str() + i + error.length())));
			i = i + error.length();
			while (isspace(_conf[i]))
				i++;
			i = i + intlen(first);
			while (isspace(_conf[i]))
				i++;
			while (isspace(_conf[i]) == 0)
			{
				second.append(1, _conf[i]);
				i++;
			}
			_errPages.push_back(std::make_pair(first, second));
			second.clear();
			if (first == 0)
			_errPages.pop_back();
		}
	i++;
	}
	/*std::vector<std::pair<int ,std::string> >::iterator it = _errPages.begin();
	while (it != _errPages.end())
	{
		std::cout << it->first << "  " << it->second << std::endl;
		it++;
	}*/
}

void ServerConf::parseName(std::string name)
{
	int i = 0;
	if ((i = _conf.find(name, i)) && i != std::string::npos)
	{
		if (isWord(i, name.length()))
		{
			i = i + name.length();
			while (isspace(_conf[i]))
				i++;
			while (isspace(_conf[i]) == 0)
			{
				_servName.append(1, _conf[i]);
				i++;
			}
		}
		i++;
	}
	if (_servName.empty())
		std::cout << "yapas" << std::endl;
	//std::cout << _servName << std::endl;
}

void ServerConf::parseRoot(std::string root)
{
	int i = 0;
	if ((i = _conf.find(root, i)) && i != std::string::npos)
	{
		if (isWord(i, root.length()))
		{
			i = i + root.length();
			while (isspace(_conf[i]))
				i++;
			while (isspace(_conf[i]) == 0)
			{
				_root.append(1, _conf[i]);
				i++;
			}
		}
		i++;
	}
	//std::cout << _root << std::endl;
}

void ServerConf::parseSize(std::string size)
{
	int i = 0;
	if ((i = _conf.find(size, i)) && i != std::string::npos)
	{
		if (isWord(i, size.length()))
			_sizeLimit = atoi((_conf.c_str() + i + size.length()));
		i = i + size.length();
	}
	if (_sizeLimit == 0)
		_sizeLimit = 500000000;
	//std::cout << _sizeLimit << std::endl;
}

void ServerConf::parsePort(std::string listen)
{
	int i = 0;
	while ((i = _conf.find(listen, i)) && i != std::string::npos)
	{
		if (isWord(i, listen.length()))
			_port.push_back(atoi((_conf.c_str() + i + listen.length())));
		i = i + listen.length();
	}
	std::vector<int>::iterator it = _port.begin();
	/*while (it != _port.end())
		std::cout << *it++ << std::endl;*/
	if (_port.empty())
		throw ParseErrorException();
}

///////////////////////////////////////////////////////////////
/////////////// UTILS FONCTIONS ///////////////////////////////

int ServerConf::cut_conf(std::string conf, int &start, int &length)
{
	int col = 0;
	int i = conf.find("server");
	if (i == std::string::npos)
		return (0);
	i = conf.find("{", i);
	i++;
	col++;
	start = i;
	while (conf[i] && col > 0)
	{
		if (conf[i] == '{')
			col++;
		if (conf[i] == '}')
			col--;
		i++;
	}
	length = i - start - 1;
	if (conf[i] == '}')
		i++;
	if (col > 0)
		return (0);
	return (i);
}

int ServerConf::isWord(int i, int incr)
{
	if ((i == 0 || isspace(_conf[i - 1])) && _conf[i + incr] == ' ')
		return (1);
	return (0);
}
