#ifndef AUTOINDEXGENERATOR_HPP
# define AUTOINDEXGENERATOR_HPP

#include <iostream>
#include <string>
#include "Webserv.h"

class AutoIndexGenerator
{

	public :

	AutoIndexGenerator();
	AutoIndexGenerator(AutoIndexGenerator const &c);
	~AutoIndexGenerator();
	void opendirectory(std::string path);
	void readDirectory(void);
	std::string getIndex(std::string path);
	std::string generateIndex(std::string path);

	private :

	struct dirent *_file;
	DIR *_dir;
	std::map<int ,std::string> _allFile;

};

#endif