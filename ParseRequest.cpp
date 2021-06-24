#include "ParseRequest.hpp"

ParseRequest::ParseRequest(std::vector<std::string> request) : _request(request), _i(0), _code(0), _size(0), _port(0), _isUpload(false)
{
	parseMethod();
	parsePath();
	parseHttp();
	parseType("Content-Type:");
	parseHost("Host:");
	parseBody();
}

ParseRequest::ParseRequest(void)
{

}

void ParseRequest::printAll(t_request t)
{
	int i = 0;
	std::cout << "method = " << t.method << std::endl;
	std::cout << "path = " << t.path << std::endl;
	std::cout << "http = " << t.host << std::endl;
	std::cout << "port = " << t.port << std::endl;
	std::cout << "type = " << t.type << std::endl;
	std::cout << "size = " << t.size << std::endl;
	std::cout << "code = " << t.code << std::endl;
	std::vector<std::string>::iterator it = _body.begin();
	while (it != _body.end())
	{
		i = i + it->length();
		std::cout << *it++ << std::endl;
	}
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
	t.isUpload = _isUpload;
	t.body = _body;
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

void ParseRequest::parseBody(void)
{
	int i = 0;
	if (_method.compare("POST") == 0)
	{
		while (i < _request.size())
		{
			if (_request[i].size() == 1)
			{
				break ;
			}
			i++;
		}
	}
	else
		return ;
	while (i < _request.size())
	{
		_body.push_back(_request[i]);
		i++;
	}
}

void ParseRequest::parseType(std::string type)
{
	int i = 0;
	while (i < _request.size() && _request[i].find(type) != 0)
	{
		i++;
	}
	if (i == _request.size())
	{
		return ;
	}
	int tmp = i;
	i = type.length();
	_type.clear();
	std::cout << i << std::endl;
	i++;
	while (isspace(_request[tmp][i]))
		i++;
	while (isspace(_request[tmp][i]) == 0 && _request[tmp][i]!= ';')
	{
		_type.append(1, _request[tmp][i]);
		i++;
	}
	if (type.compare("multipart/form-data") == 0)
	{
		_isUpload = true;
	}
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