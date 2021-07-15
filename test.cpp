#include "Webserv.h"
#include <map>
 #include <sys/wait.h>
 #include <stdlib.h>
int main()
{
	int i = remove("ok");
	std::cout << i << std::endl;
}
