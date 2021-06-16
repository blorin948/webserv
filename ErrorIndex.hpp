#ifndef ERRORINDEX_HPP
# define ERRORINDEX_HPP

#include <iostream>
#include <string>
#include "Webserv.h"
#include "GetResponse.hpp"

class ErrorIndex
{

	public :

	ErrorIndex(int code);
	ErrorIndex();
	void readDirectory(void);
	void opendirectory(void);
	void printall(void);
	std::string defaultPage(void);
	std::string getPage(int code);
	std::string getError();
	ErrorIndex(ErrorIndex const &c);
	ErrorIndex &operator=(ErrorIndex const &c);
	~ErrorIndex();

	private :

	void intToStr(int code);
	int _code;
	DIR *_dir;
	struct dirent *_file;
	std::string _strcode;
	std::vector<std::string > _allFile;
};

#endif