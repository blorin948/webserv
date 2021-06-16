#include "ServerConf.hpp"

ServerConf::ServerConf(std::string &conf) : _errorParsing(false)
{
	int start = 0;
	int length = 0;
	int end = cut_conf(conf, start, length);
	_conf = conf.substr(start, length);
	start = conf.find("server");
	conf.erase(0, end + start);
	parseAll();
}

void ServerConf::parseAll(void)
{
	parsePort();
}

void ServerConf::parsePort(void)
{
	int i = 0;
	while ((i = _conf.find("listen", i)) && i != std::string::npos)
	{
		if ((i == 0 || isspace(_conf[i - 1])) && _conf[i + 6] == ' ')
		{
			_port.push_back(atoi((_conf.c_str() + i + 6)));
		}
		i = i + 6;
	}
	std::vector<int>::iterator it = _port.begin();
	while (it != _port.end())
		std::cout << *it++ << std::endl;
	if (_port.empty())
		_errorParsing = true;
	// ou enoyer une exception
}

ServerConf::ServerConf(void)
{

}

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

ServerConf::ServerConf(ServerConf const &c)
{
	*this = c;
}

ServerConf &ServerConf::operator=(ServerConf const &c)
{
	return (*this);
}

ServerConf::~ServerConf()
{

}