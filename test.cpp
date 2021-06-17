#include "ServerConf.hpp"

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
	try
	{
		ServerConf t(file);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	//std::cout << file << std::endl;
}