#include "ParseRequest.hpp"

ParseRequest::ParseRequest(std::vector<std::string> request) : _request(request), _i(0), _code(0), _size(0), _port(0)
{
	parseMethod();
	parsePath();
	parseHttp();
	parseHost("Host:");
}

ParseRequest::ParseRequest(void)
{

}

void ParseRequest::getRequest(t_request &t)
{
	t.method = _method;
	t.size = _size;
	t.path = _path;
	t.http = _http;
	t.host = _host;
	t.port = _port;
	t.type = _type;
	t.code = _code;
}

void ParseRequest::parseHost(std::string host)
{
	int i = 0;
	int h = 0;
	int tmp = 0;
	while (i < _request.size())
	{
		if (_request[i].compare(0, host.length(), host) == 0)
		{
			h++;
			tmp = i;
		}
		i++;
	}
	std::cout << tmp << std::endl;
	if (h != 1)
	{
		_code = 400;
		return ;
	}
	i = 0;
	i = host.length();
	while (isspace(_request[tmp][i]))
		i++;
	while (isspace(_request[tmp][i]) == 0 && _request[tmp][i]!= ':')
	{
		_host.append(1, _request[tmp][i]);
		i++;
	}
	if (_request[tmp][i] == ':')
	{
		i++;
		_port = atoi(_request[tmp].c_str() + i);
	}
	//std::cout << _host << " + " << _port<< std::endl;
}

void ParseRequest::parseHttp(void)
{
	while (isspace(_request[0][_i]))
		_i++;
	while (isspace(_request[0][_i]) == 0)
	{
		_http.append(1, _request[0][_i]);
		_i++;
	}
	std::cout << _http << std::endl;
	_i = 0;
	if (_http.empty() || _path.empty() || _method.empty())
		_code = 400;
	if (_http.compare("HTTP/1.1") != 0)
		_code = 400;
}

void ParseRequest::parsePath(void)
{
	while (isspace(_request[0][_i]))
		_i++;
	while (isspace(_request[0][_i]) == 0)
	{
		_path.append(1, _request[0][_i]);
		_i++;
	}
	//std::cout << _path << std::endl;
}

void ParseRequest::parseMethod(void)
{
	while (isspace(_request[0][_i]) == 0)
	{
		_method.append(1, _request[0][_i]);
		_i++;
	}
	//std::cout << _method << std::endl;
}

ParseRequest::ParseRequest(ParseRequest const &c)
{
	*this = c;
}

ParseRequest &ParseRequest::operator=(ParseRequest const &c)
{
	return (*this);
}

ParseRequest::~ParseRequest()
{

}