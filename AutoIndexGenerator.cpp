#include "AutoIndexGenerator.hpp"

AutoIndexGenerator::AutoIndexGenerator(void)
{

}

std::string AutoIndexGenerator::generateIndex(std::string path)
{
	opendirectory(path);
	readDirectory();
	return (getIndex(path));
}

std::string AutoIndexGenerator::getIndex(std::string path)
{
	int i = 0;
	std::stringstream ss;
	std::string ret;
	ss << "<!DOCTYPE html>\n";
	if (path.compare("www/") != 0)
	{
		ss << "<p><a style=text-decoration:none href= .. > . . </a></p>\n";
	}
	while (i < _allFile.size())
	{
		if (_allFile[i].first == DT_DIR)
			ss << "<p><a href=" + _allFile[i].second + "/>" + _allFile[i].second + "/</a></p>\n";
		else
			ss << "<p><a href=" + _allFile[i].second + ">" + _allFile[i].second + "</a></p>\n";
		i++; 
	}
	ret = ss.str();
	return ret;
}

void AutoIndexGenerator::readDirectory(void)
{
	int first;
	std::string second;
	while ((_file = readdir(_dir)) != NULL)
	{
		if (_file->d_name[0] != '.')
		{
			first = _file->d_type;
			second = _file->d_name;
			std::pair<int, std::string> tmp;
			tmp.first = first;
			tmp.second = second;
			_allFile.push_back(tmp);
		}
	}
	//printall();
}

void AutoIndexGenerator::opendirectory(std::string path)
{
	_dir = opendir(path.c_str());
	std::cout << path.c_str() << std::endl;
	if (_dir == NULL)
		throw std::runtime_error("error with index");
}

AutoIndexGenerator::AutoIndexGenerator(AutoIndexGenerator const &c)
{
	*this = c;
}

AutoIndexGenerator &AutoIndexGenerator::operator=(AutoIndexGenerator const &c)
{
	return (*this);
}

AutoIndexGenerator::~AutoIndexGenerator()
{

}