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
