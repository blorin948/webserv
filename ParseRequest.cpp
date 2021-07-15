#include "ParseRequest.hpp"

ParseRequest::ParseRequest() : _i(0), _code(0), _size(0), _port(0), _isUpload(false)
{

}

int ParseRequest::getBodyLength(void)
{
	return _body.length();
}

void ParseRequest::getRequest(t_request &t, std::vector<std::string> req)
{
	_request = req;
	int i = 0;
/*	while (i < _request.size())
	{
		std::cout <<"dans le parsing = " <<  _request[i] << std::endl;
		i++;
	}*/
	initRequest(t);
	parseMethod();
	parsePath();
	parseHttp();
	parseType("Content-Type:");
	parseHost("Host:");
	if (_isUpload == true)
		parseBodyUpload();
	else
		parseBody();
	_size = getBodyLength();
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
	t.uploadName = _uploadName;
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
	while (_i != _request[0].size() && isspace(_request[0][_i]) == 0)
	{
		_http.append(1, _request[0][_i]);
		_i++;
	}
	//std::cout << _http << std::endl;
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
//	std::cout << "path = "<<_path << std::endl;
}

void ParseRequest::parseMethod(void)
{
	while (isspace(_request[0][_i]) == 0)
	{
		_method.append(1, _request[0][_i]);
		_i++;
	}
	//std::cout << "meth = " <<_method << std::endl;
}

void ParseRequest::parseBody(void)
{
	int i = 0;
	if (_method.compare("POST") != 0)
		return ;
	_body = _request[_request.size() - 1];
}

void ParseRequest::parseBodyUpload(void)
{
	int i = 0;
	int start;
	if (_method.compare("POST") != 0)
	{
		return ;
	}
	std::string reqBody = _request[_request.size() - 1];
		// Get file name //
		i = reqBody.find("filename=");
		i = i + 10;
		while (i != reqBody.find("\"", i))
		{
			_uploadName.append(1, reqBody[i]);
			i++;
		}
		i = reqBody.find("\n", i);
		i++;
		i = reqBody.find("\n", i);
		i++;
		start = i;
		i = reqBody.find(_boundary, i);
		// Get body of file //
		_body = reqBody.substr(start, i - start);
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
	i++;
	while (isspace(_request[tmp][i]))
		i++;
	while (isspace(_request[tmp][i]) == 0 && _request[tmp][i]!= ';')
	{
		_type.append(1, _request[tmp][i]);
		i++;
	}
	if (_type.compare("multipart/form-data") == 0)
		_isUpload = true;
	else
		return ;
	i = _request[tmp].find("=", i);
	i++;
	if (i != std::string::npos)
	{
		_boundary = _request[tmp].substr(i);
		_boundary.insert(0, "--");
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