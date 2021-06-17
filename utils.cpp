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