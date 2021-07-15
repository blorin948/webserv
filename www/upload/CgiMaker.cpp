
#include "CgiMaker.hpp"

CgiMaker::CgiMaker(void)
{

}

int CgiMaker::isCgiFile(t_request req, RouteConf* route)
{
	int start = route->getPath().size();
	int end;
	int i = start;
	while (i < req.path.size() && req.path[i] != '/' && req.path[i] != '?')
	{
		i++;
	}
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
	std::cout << "length = " << _path_WO_query <<std::endl;
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
	int a = 0;
	if (req.method.compare("POST") == 0)
	{
		_length = intToString(req.body.size());
		while (a < req.body.size())
		{
		std::cout << "llala" << std::endl;
			_body += req.body[a];
			a++;
		}
		return ;
	}
	int i = 0;
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

int CgiMaker::execute_cgi(t_request req, RouteConf *route)
{
	char **Env = mapToChar(_env);
	char **arg = {NULL};
	int saveIn = dup(STDIN_FILENO);
	int saveOut = dup(STDOUT_FILENO);
	char str[100];
	std::string buffer;
	FILE *out = tmpfile();
	FILE *in = tmpfile();
	int fd_in = fileno(in);
	int fd_out = fileno(out);
	std::cout << "body = " << _body << std::endl;
	write(fd_in, _body.c_str(), _body.length());
	lseek(fd_in, 0, SEEK_SET);
	int f = fork();
	if (f == 0)
	{
		dup2(fd_in, STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		execve("cgi_tester", arg, Env);
		throw(std::runtime_error("c bon"));
	}
	else
	{
		wait(0);
		lseek(fd_out, 0, SEEK_SET);
		int ret = 1;
		memset(str, 0, 100);
		while (ret > 0)
		{
			ret = read(fd_out, str, 100);
			buffer = buffer + str;
		}
	}
	dup2(saveIn, STDIN_FILENO);
	dup2(saveOut, STDOUT_FILENO);
	close(fd_out);
	close(fd_in);
	close(saveOut);
	close(saveIn);
	std::cout << "|" << str << "|" <<std::endl;
	return (1);
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
		int i = req.path.find("?");
		int a = 0;
		std::cout << "sassaas = " <<req.path<< std::endl;
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
	execute_cgi(req, route);
	return res;
}


char **CgiMaker::mapToChar(std::map<std::string, std::string> env)
{
	char **result;
	std::map<std::string, std::string>::iterator it;
	size_t i;

	if (!(result = (char **)malloc(sizeof(char *) * (env.size() + 1))))
		return (0);
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

CgiMaker &CgiMaker::operator=(CgiMaker const &c)
{
	return (*this);
}

CgiMaker::~CgiMaker()
{

}
