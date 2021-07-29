#include "includes/CgiMaker.hpp"

CgiMaker::CgiMaker(void)
{

}

int CgiMaker::isCgiFile(t_request req, RouteConf* route)
{
	unsigned long start = route->getPath().size();
	unsigned long end;
	unsigned long i = start;
	while (i < req.path.size() && req.path[i] != '/' && req.path[i] != '?')
		i++;
	end = i;
	i = req.path.find(".bla", start);
	i = i + 4;
	if (i != end)
		return (0);
	else
		return (1);
}


int CgiMaker::is_cgi(t_request req, RouteConf* route)
{
	
	if (route->getIsCgi() == false)
	{
		return (0);
	}
	if ((req.method.compare("POST") != 0) && (req.method.compare("GET") != 0))
		return (0);
	if (isCgiFile(req, route) == 0)
		return 0;
	return (1);
}

void CgiMaker::create_env(t_request req, RouteConf* route)
{
	_env["SERVER_SOFTWARE"] = "Webserv";
	_env["SERVER_NAME"] = route->getServName();
	_env["GATEWAY_INTERFACE"] = "CGI/1.1";
	_env["SERVER_PROTOCOL"] = "HTTP/1.1";
	_env["SERVER_PORT"] = req.port;
	_env["REQUEST_METHOD"] = req.method;
	_env["PATH_INFO"] = _path_WO_query;
	_env["QUERY_STRING"]= _query;
	_env["REMOTE_HOST"] = route->getServName();
	_env["CONTENT_LENGTH"] = _length;
	_env["CONTENT_TYPE"] = "Content-Type: text/html";
}

void CgiMaker::setQuery(t_request req)
{
	if (req.method.compare("POST") == 0)
	{
		_length = intToString(req.body.size());
		_body = req.body;
		return ;
	}
	unsigned long i = 0;
	i = req.path.find("?");
	if (i == std::string::npos)
	{
		_length = "0";
		return ;
	}
	else
	{
		i++;
		while (i < req.path.size())
		{
			_query.append(1, req.path[i]);
			i++;
		}
	}
	_body = _query;
	_length = intToString(_query.size());
}

int CgiMaker::execute_cgi(RouteConf *route)
{
	if (_body.length() > route->getMaxBodySize())
	{
		throw (std::runtime_error("body too big"));
	}
	char **Env = mapToChar(_env);
	char **arg = {NULL};
	int saveIn = dup(STDIN_FILENO);
	int saveOut = dup(STDOUT_FILENO);
	int i = 1;
	int succes = 1;
	char str[100];
	std::string buffer;
	FILE *out = tmpfile();
	FILE *in = tmpfile();
	int fd_in = fileno(in);
	int fd_out = fileno(out);
	write(fd_in, _body.c_str(), _body.length());
	lseek(fd_in, 0, SEEK_SET);
	int es = 0;
	int f = fork();
	if (f == 0)
	{
		dup2(fd_in, STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		execve(route->getCgiPath().c_str(), arg, Env);
		exit(1);
		//throw (std::runtime_error("bad cgi script"));
	}
	else
	{
		int status;
		if ( waitpid(f, &status, 0) == -1 ) 
		{
			perror("waitpid failed");
			return EXIT_FAILURE;
    	}
		if ( WIFEXITED(status) ) 
			es = WEXITSTATUS(status);
		if (es == 1)
			succes = 0;
		//waitpid(-1, NULL, 0);
		lseek(fd_out, 0, SEEK_SET);
		int ret = 1;
		while (ret > 0)
		{
			memset(str, 0, 100);
			ret = read(fd_out, str, 100);
			buffer.append(str);
		}
	}
	dup2(saveIn, STDIN_FILENO);
	dup2(saveOut, STDOUT_FILENO);
	close(fd_out);
	close(fd_in);
	close(saveOut);
	close(saveIn);
	_buffer = buffer;
	i = 0;
	while (Env[i])
	{
		delete[] Env[i];
		i++;
	}
	delete[] Env;
	return (succes);
}

std::string CgiMaker::getBuffer(void) const
{
	return _buffer;
}

void CgiMaker::set_path(t_request req)
{
	if (req.method.compare("POST") == 0)
	{
		_path_WO_query = req.path;
		return ;
	}
	else if (req.method.compare("GET") == 0)
	{
		unsigned long i = req.path.find("?");
		unsigned long a = 0;
		if (i != std::string::npos)
		{
			while (a < i)
			{
				_path_WO_query.append(1, req.path[a]);
				a++;
			}
		}
		else
			_path_WO_query = req.path;
	}
}

std::string CgiMaker::parseType(std::string type)
{
	unsigned long i = 0;
	std::string Restype;
	if ((i = _buffer.find(type, i)) && i != std::string::npos)
	{
		if (isWord(i, type.length(), _buffer))
		{
			i = i + type.length();
			while (isspace(_buffer[i]))
				i++;
			while (_buffer[i] != '\n')
			{
				Restype.append(1, _buffer[i]);
				i++;
			}
		}
		i++;
	}
	return Restype;
}

int CgiMaker::parseCode(std::string status)
{
	unsigned long i = 0;
	std::string code;
	i = _buffer.find(status, i);
	if (i != std::string::npos)
	{
		i = _buffer.find(status, i);
		if (isWord(i, status.length(), _buffer))
		{
			i = i + status.length();
			while (isspace(_buffer[i]))
				i++;
			while (isspace(_buffer[i]) == 0)
			{
				code.append(1, _buffer[i]);
				i++;
			}
		}
		i++;
	}
	return atoi(code.c_str());
}

std::string CgiMaker::parseBody(void)
{
	unsigned long i = 0;
	std::string body;
	i = _buffer.find("\r\n\r\n");
	i = i +4;
	while (i < _buffer.size())
	{
		body.append(1, _buffer[i]);
		i++;
	}
	return body;
}

t_response CgiMaker::parseCgi(t_response res)
{
	res.code = parseCode("Status:");
	res.type = parseType("Content-Type:");
	res.body = parseBody();
	return res;
}

t_response CgiMaker::make_cgi(t_response res, t_request req, RouteConf* route)
{
	t_response t;
	t = res;
	set_path(req);
	_full_path = route->getRoot();
	_full_path.resize(_full_path.size() - 1);
	_full_path += req.path;
	setQuery(req);
	create_env(req, route);
	try
	{
		if (execute_cgi(route) == 0)
		{
			res.code = 500;
			return res;
		}
		res = parseCgi(res);
	}
	catch(const std::exception& e)
	{
		if (strcmp(e.what(), "bad cgi script") == 0 )
			res.code = 500;
		if (strcmp(e.what(), "body too big") == 0 )
			res.code = 413;
	}
	return res;
}


char **CgiMaker::mapToChar(std::map<std::string, std::string> env)
{
	char **result;
	std::map<std::string, std::string>::iterator it;
	size_t i;

	result = new char*[env.size() + 1];
	it = env.begin();
	i = 0;
	while (it != env.end())
	{
		result[i++] = newStr(it->first + "=" + it->second);
		++it;
	}
	result[env.size()] = 0;
	return (result);
}

CgiMaker::CgiMaker(CgiMaker const &c)
{
	*this = c;
}

CgiMaker::~CgiMaker()
{
	_env.clear();
}