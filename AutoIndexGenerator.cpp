#include "includes/AutoIndexGenerator.hpp"

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
	std::stringstream ss;
	std::string ret;
	ss << "<!DOCTYPE html>\n";
	if (path.compare("www/") != 0)
	{
		ss << "<p><a style=text-decoration:none href= .. > . . </a></p>\n";
	}
	std::map<int, std::string>::iterator it;
	it = _allFile.begin();
	while (it != _allFile.end())
	{
		if (it->first < 0)
			ss << "<p><a href=" + it->second + "/>" + it->second + "/</a></p>\n";
		else
			ss << "<p><a href=" + it->second + ">" + it->second + "</a></p>\n";
		it++; 
	}
	ret = ss.str();
	return ret;
}

void AutoIndexGenerator::readDirectory(void)
{
	int first;
	int file = 1;
	int dir = -1;
	std::string second;
	while ((_file = readdir(_dir)) != NULL)
	{
		if (_file->d_name[0] != '.')
		{
			if (_file->d_type == DT_DIR)
			{
				first = dir;
				dir--;
			}
			else
			{
				first = file;
				file++;
			}
			second = _file->d_name;
			std::pair<int, std::string> tmp;
			tmp.first = first;
			tmp.second = second;
			_allFile.insert(tmp);
		}
	}
	//printall();
}

void AutoIndexGenerator::opendirectory(std::string path)
{
	_dir = opendir(path.c_str());
	if (_dir == NULL)
		throw std::runtime_error("error with index");
}

AutoIndexGenerator::AutoIndexGenerator(AutoIndexGenerator const &c)
{
	*this = c;
}

AutoIndexGenerator::~AutoIndexGenerator()
{
	_allFile.clear();
	closedir(_dir);
	delete _file;
}