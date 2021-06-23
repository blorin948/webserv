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