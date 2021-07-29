#include "includes/ServerConf.hpp"

ServerConf::ServerConf(std::string &conf) : _errorParsing(false),  _default(false), _can_upload(false), _can_accept(false) ,_i(0), _sizeLimit(0)
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

void ServerConf::set_can_accept_connection(bool accept)
{
	_can_accept = accept;
}

bool ServerConf::get_can_accept_connection(void)
{
	return _can_accept;
}

void ServerConf::setDefault(bool defaulte)
{
	_default = defaulte;
}

t_response ServerConf::response_from_server(t_response res, t_request req)
{
	t_response t = res;
	t.oldpath = req.path;
	if (req.code > 0)
	{
		t.code = req.code;
		t.method = "GET";
		t.errPages = _errPages;
		return (t);
	}
	t.method = req.method;
	req.path.erase(0, 1);
	t.path = _root + req.path;
	t.errPages = _errPages;
	t.maxBodySize = _sizeLimit;
	return (t);
}

bool ServerConf::isRoute(t_request req) const
{
	unsigned long i = 0;
	while (i < _route.size())
	{
		if (req.path.compare(0, _route[i]->getPath().length(), _route[i]->getPath()) == 0)
			return true;
		i++;
	}
	return false;
}

t_response ServerConf::getReponse(t_response res, t_request req)
{
	unsigned long i = 0;
	while (i < _route.size())
	{
		if (req.path.compare(0, _route[i]->getPath().length(), _route[i]->getPath()) == 0)
		{
			res = _route[i]->getReponse(res, req);
			break ;
		}
		i++;
	}
	if (i == _route.size())
		res = response_from_server(res, req);
	return (res);
}

void ServerConf::splitConfRoute(std::string location)
{
	int length = 0;
	unsigned long i = 0;
	std::string route;
	while ((i = _conf.find(location, i)) && i != std::string::npos)
	{
		if (isWord(i, location.length(), _conf))
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

int ServerConf::routeLength(unsigned long i)
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


void ServerConf::tri_bulle()
{
    int passage = 0;
    bool permutation = true;
    unsigned long en_cours = 0;
    while ( permutation) 
	{
        permutation = false;
        passage ++;
        for (en_cours = 0 ; en_cours <_route.size()  - passage ; en_cours++) 
		{
            if (_route[en_cours]->getSizePath() < _route[en_cours+1]->getSizePath())
			{
                permutation = true;
                // on echange les deux elements
                RouteConf *temp = _route[en_cours];
                _route[en_cours] = _route[en_cours+1];
                _route[en_cours+1] = temp;
            }
        }
    }
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
		_route[i]->parseLocation();
		i++;
	}
	tri_bulle();
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

ServerConf::~ServerConf()
{
	_conf.clear();
	_servName.clear();
	_root.clear();
	_port.clear();
	_errPages.clear();
	_route.clear();
}

///////////////////////////////////////////////////////////////
/////////////// GET FONCTIONS /////////////////////////////////

RouteConf *ServerConf::getCurrentRoute(t_request req) const
{
	unsigned long i = 0;
	while (i < _route.size())
	{
		if (req.path.compare(0, _route[i]->getPath().length(), _route[i]->getPath()) == 0)
		{
			return _route[i];
			break ;
		}
		i++;
	}
	return (_route[_i]);
}

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

std::map<int, std::string> ServerConf::getErrPages() const
{
	return (_errPages);
}
///////////////////////////////////////////////////////////////
/////////////// PARSING FONCTIONS /////////////////////////////

void ServerConf::parseError(std::string error)
{
	unsigned long i = 0;
	int first = 0;
	std::string second;
	while ((i = _conf.find(error, i)) && i != std::string::npos)
	{
		if (isWord(i, error.length(), _conf))
		{
			first = (atoi((_conf.c_str() + i + error.length())));
			i = i + error.length();
			while (isspace(_conf[i]))
				i++;
			i = i + intlen(first);
			while (isspace(_conf[i]) && _conf[i] != '\n' )
				i++;
			while (isspace(_conf[i]) == 0)
			{
				second.append(1, _conf[i]);
				i++;
			}
			if (first == 0 || second.empty())
				throw std::runtime_error("Error with Error files");
			_errPages.insert(std::pair<int, std::string>(first, second));
			second.clear();
			
		}
	i++;
	}
}

void ServerConf::parseName(std::string name)
{
	unsigned long i = 0;
	if ((i = _conf.find(name, i)) && i != std::string::npos)
	{
		if (isWord(i, name.length(), _conf))
		{
			i = i + name.length();
			while (isspace(_conf[i]) && _conf[i] != '\n')
				i++;
			while (isspace(_conf[i]) == 0)
			{
				_servName.append(1, _conf[i]);
				i++;
			}
		}
		i++;
		if (_servName.empty())
			throw std::runtime_error("Error with server name");
	}
}

void ServerConf::parseRoot(std::string root)
{
	unsigned long i = 0;
	if ((i = _conf.find(root, i)) && i != std::string::npos)
	{
		if (isWord(i, root.length(), _conf))
		{
			i = i + root.length();
			while (isspace(_conf[i]) && _conf[i] != '\n')
				i++;
			while (isspace(_conf[i]) == 0)
			{
				_root.append(1, _conf[i]);
				i++;
			}
		}
		i++;
		if (_root.empty())
			throw std::runtime_error("Error with root");
	}
}

void ServerConf::parseSize(std::string size)
{
	unsigned long i = 0;
	if ((i = _conf.find(size, i)) && i != std::string::npos)
	{
		if (isWord(i, size.length(), _conf))
			_sizeLimit = atoi((_conf.c_str() + i + size.length()));
		i = i + size.length();
	}
	if (_sizeLimit == 0)
		_sizeLimit = 500000000;
}

void ServerConf::parsePort(std::string listen)
{
	unsigned long i = 0;
	while ((i = _conf.find(listen, i)) && i != std::string::npos)
	{
		if (isWord(i, listen.length(), _conf))
			_port.push_back(atoi((_conf.c_str() + i + listen.length())));
		i = i + listen.length();
	}
	if (_port.empty())
		throw ParseErrorException();
}

///////////////////////////////////////////////////////////////
/////////////// UTILS FONCTIONS ///////////////////////////////

int ServerConf::cut_conf(std::string conf, int &start, int &length)
{
	int col = 0;
	unsigned long i = conf.find("server");
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
