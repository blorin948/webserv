#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <sstream> 
#include <fstream> 

int main()
{
	std::string ok;
	char ok1[] = "salut";
	ok = ok1;
	std::cout << ok << std::endl;
}