#include "Webserv.h"
#include "ErrorIndex.hpp"

int parse_conf(std::string conf)
{

}

int main()
{
	std::ostringstream buf;
	std::string file;
	std::ifstream myfile("test.conf", std::ifstream::in);
	if (!(myfile.is_open()))
		return 404;
	while (getline(myfile, file))
	{
		buf << file;
		buf << "\n";
	}
	file = buf.str();
	ServerConf t(file);
	//std::cout << file << std::endl;
}