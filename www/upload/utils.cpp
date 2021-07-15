
#include "Webserv.h"

int intlen(int i)
{
	int count = 0;
	while (i > 0)
	{
		i/=10;
		count++;
	}
	return (count);
}

int isWord(int i, int incr, std::string str)
{
	if ((i == 0 || isspace(str[i - 1])) && str[i + incr] == ' ')
		return (1);
	return (0);
}

std::string intToString(int i)
{
	std::stringstream ss;
	ss << i;
	std::string str = ss.str();
	return (str);
}

void printResponse(t_response t)
{
	std::cout << "method = " << t.method << std::endl;
	std::cout << "path = " << t.path << std::endl;
	std::cout << "location = " << t.location << std::endl;
	std::cout << "code = " << t.code << std::endl;
	std::cout << "defaultDir = " << t.defaultDir << std::endl;
}

void printAllRequest(t_request t)
{
	int i = 0;
	std::cout << "method = " << t.method << std::endl;
	std::cout << "path = " << t.path << std::endl;
	std::cout << "http = " << t.host << std::endl;
	std::cout << "port = " << t.port << std::endl;
	std::cout << "type = " << t.type << std::endl;
	std::cout << "size = " << t.size << std::endl;
	std::cout << "code = " << t.code << std::endl;
	std::cout << "uploadName = " << t.uploadName << std::endl;
	std::cout << "body = " << t.body <<std::endl;
}

bool IsPathExist(const std::string &s)
{
  struct stat buffer;
  return (stat (s.c_str(), &buffer) == 0);
}

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

-----------------------------35599871678755532882088138597
Content-Disposition: form-data; name="submit"

Upload
-----------------------------35599871678755532882088138597--
