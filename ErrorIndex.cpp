#include "ErrorIndex.hpp"

ErrorIndex::ErrorIndex(int code) : _code(code)
{
	opendirectory();
	readDirectory();
}

void ErrorIndex::intToStr(int code)
{
	std::stringstream ss;
	ss << code;
	_strcode = ss.str();
}

std::string defaultPage(void)
{

}

std::string ErrorIndex::getPage(int code)
{
	intToStr(code);
	std::vector<std::string>::iterator it = _allFile.begin();
	GetResponse t;
	while (it != _allFile.end())
	{
		if (it->find(_strcode) != std::string::npos)
		{
			break ;
		}
		it++;
	}
	if (it == _allFile.end())
	{
		return t.getErrorPage("", "");
	}
	return t.getErrorPage(*it, _strcode);
}

void ErrorIndex::readDirectory(void)
{
	while ((_file = readdir(_dir)) != NULL)
	{
		if (_file->d_type == DT_REG)
		{
			if (_file->d_name[0] != '.')
				_allFile.push_back(_file->d_name);
		}
	}
	//printall();
}

void ErrorIndex::printall(void)
{
	std::vector<std::string>::iterator it = _allFile.begin();
	while (it != _allFile.end())
		std::cout << *it++ << std::endl;
	
}

void ErrorIndex::opendirectory(void)
{
	_dir = opendir("./Error/");
	if (_dir == NULL)
		std::cout << "error" << std::endl;

}

ErrorIndex::ErrorIndex(void)
{
	opendirectory();
	readDirectory();
}

ErrorIndex::ErrorIndex(ErrorIndex const &c)
{
	*this = c;
}

ErrorIndex &ErrorIndex::operator=(ErrorIndex const &c)
{
	return (*this);
}

ErrorIndex::~ErrorIndex()
{

}