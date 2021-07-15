
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
	env["CONTENT_LENGTH"] = "5";
	env["PATH_INFO"] = "youpi.bla";
	env["SERVER_PROTOCOL"] = "HTTP/1.1";
	env["QUERY_STRING"] = "?name=asd";
	env["CONTENT_TYPE"] = "Content-Type: text/html";
}
 #include <stdlib.h>
int main()
{
	try
	{
		std::map<std::string, std::string>	env = initEnv();
		char **Env = convertParams(env);
		char **arg = {NULL};
		int saveIn = dup(STDIN_FILENO);
		int saveOut = dup(STDOUT_FILENO);
		std::ostringstream ss;
		std::string s;
		char str[5000];
		FILE *out = tmpfile();
		FILE* in = tmpfile();
		int fd_in = fileno(in);
		int fd_out = fileno(out);
		int f = fork();
		write(fd_in, "o", 5);
		lseek(fd_in, 0, SEEK_SET);
		dup2(fd_in, STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		if (f == 0)
		{
			execve("cgi_tester", arg, Env);
			throw (std::runtime_error("c bon"));
		}
		else
		{
			wait(0);
			lseek(fd_out, 0, SEEK_SET);
			read(fd_out, str, 5000);
		}
		dup2(saveIn, STDIN_FILENO);
		dup2(saveOut, STDOUT_FILENO);
		close(fd_out);
		close(fd_in);
		close(saveOut);
		close(saveIn);
		std::cout<< str << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		exit(0);
	}
	std::cout << "saluuuuuut" << std::endl;
}

