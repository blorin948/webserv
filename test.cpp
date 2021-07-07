#include "Webserv.h"
#include <map>
 #include <sys/wait.h>
char *newStr(std::string source)
{
	char *res;

	if (!(res = (char *)malloc(sizeof(char) * (source.size() + 1))))
		return (0);
	for (size_t i = 0; i < source.size(); ++i)
		res[i] = source[i];
	res[source.size()] = 0;
	return (res);
}



char **convertParams(std::map<std::string, std::string> args)
{
	char **result;
	std::map<std::string, std::string>::iterator it;
	size_t i;

	if (!(result = (char **)malloc(sizeof(char *) * (args.size() + 1))))
		return (0);
	it = args.begin();
	i = 0;
	while (it != args.end())
	{
		result[i++] = newStr(it->first + "=" + it->second);
		++it;
	}
	result[args.size()] = 0;
	return (result);
}

std::map<std::string, std::string>	initEnv() 
{
	std::map<std::string, std::string>	env;

	 //Security needed to execute php-cgi
	env["GATEWAY_INTERFACE"] = "CGI/1.1";
	env["SERVER_NAME"] = "localhost";
	env["SCRIPT_FILENAME"] = "youpi.bla";
	env["REQUEST_METHOD"] = "GET";
	env["CONTENT_LENGTH"] = "1";
	env["PATH_INFO"] = "youpi.bla";
	env["SERVER_PROTOCOL"] = "HTTP/1.1";
	env["QUERY_STRING"] = "?name=asd";
	env["CONTENT_TYPE"] = "Content-Type: text/html";
	/*this->_env["PATH_TRANSLATED"] = request.getPath(); //might need some change, using config path/contentLocation
	this->_env["REMOTEaddr"] = to_string(config.getHostPort().host);
	this->_env["REMOTE_IDENT"] = headers["Authorization"];
	this->_env["REMOTE_USER"] = headers["Authorization"];
	this->_env["REQUEST_URI"] = request.getPath() + request.getQuery();
	if (headers.find("Hostname") != headers.end())
	else
		this->_env["SERVER_NAME"] = this->_env["REMOTEaddr"];
	this->_env["SERVER_PORT"] = to_string(config.getHostPort().port);
	this->_env["SERVER_SOFTWARE"] = "Weebserv/1.0";*/
	return env;
}

int main()
{
	std::map<std::string, std::string>	env = initEnv();
	char **Env = convertParams(env);
	char **arg = {NULL};
	int i = fork();
	if (i == 0)
	execve("cgi_tester", arg, Env);
	else
	wait(0);
}