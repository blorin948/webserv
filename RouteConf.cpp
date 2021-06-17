#include "RouteConf.hpp"

RouteConf::RouteConf()
{
	
}

RouteConf::RouteConf(RouteConf const &c)
{
	*this = c;
}

RouteConf &RouteConf::operator=(RouteConf const &c)
{
	return (*this);
}

RouteConf::~RouteConf()
{

}

void RouteConf::printAll(void)
{
	std::cout << "ici la route" << std::endl;
	std::vector<int>::iterator it1 = _port.begin();
	while (it1 != _port.end())
		std::cout << *it1++ << std::endl;
	std::cout << _servName << std::endl;
	std::cout << _root << std::endl;
	std::cout << _sizeLimit << std::endl;
	std::vector<std::pair<int ,std::string> >::iterator it = _errPages.begin();
	while (it != _errPages.end())
	{
		std::cout << it->first << "  " << it->second << std::endl;
		it++;
	}
	std::cout << _conf << std::endl;
}

void RouteConf::setRoot(std::string root)
{
	_root = root;
}

void RouteConf::setConf(std::string conf)
{
	_conf = conf;
}

void RouteConf::setName(std::string name)
{
	_servName = name;
}

void RouteConf::setPort(std::vector <int> port)
{
	_port = port;
}

void RouteConf::setErrPages(std::vector <std::pair<int, std::string> > errPages)
{
	_errPages = errPages;
}

void RouteConf::setLimit(unsigned int sizeLimit)
{
	_sizeLimit = sizeLimit;
}

std::string RouteConf::getRoot(void) const
{
	return _root;
}


