#include "GetResponse.hpp"

GetResponse::GetResponse() : _defaultError("Error/Default.html")
{

}


void GetResponse::setName(void)
{
	int i = 4;
	while (_request[0][i] != 32)
		i++;
	this->_name = _request[0].substr(5, _request[0].find(" ", 4) - 5);
}

bool GetResponse::isDirectory(std::string path)
{
	int i  = path.find_last_of("/");
	if (i == path.size() -1)
	{
		std::cout << "dir" << std::endl;
		return (true);
	}
	else
	return false;
}

std::string GetResponse::handle_dir(t_response res)
{
	if (res.autoindex == true)
	{
		AutoIndexGenerator t;
		std::string ret;
		_file = t.generateIndex(res.path);
		return (setAll(200));
	}
	else if (res.defaultDir.empty() == 0)
	{
		res.code = openFile(res.defaultDir);
		return setAll(res.code);
	}
	else
	{
		res.code = openFile(_defaultError);
		return setAll(res.code);
	}
}

int GetResponse::isDir(t_response t)
{
	struct stat s;
	std::ostringstream buf;
	std::ifstream myfile(t.path, std::ifstream::in);
	if (!(myfile.is_open()))
		return (0);
	stat(t.path.c_str(), &s);
	if (S_ISDIR(s.st_mode))
		return (1);
	return (0);
}

void GetResponse::modifyIfDir(t_response &t)
{
	struct stat s;
	std::ostringstream buf;
	std::ifstream myfile(t.path, std::ifstream::in);
	if (!(myfile.is_open()))
		return ;
	stat(t.path.c_str(), &s);
	if (S_ISDIR(s.st_mode))
		t.path.push_back('/');
}

std::string GetResponse::getFullResponse(t_response res)
{
	if (res.code >= 400)
		return (getErrorPage(res));
	if (isDir(res) && res.code != 301 && (res.path[res.path.size() - 1] != '/'))
	{
		res.code = 301;
		res.location = res.oldpath;
		res.location.push_back('/');
		std::cout << "redir de dir " + res.location << std::endl;
	}
	if (res.code == 301)
		return (redirectPage(res));
	else
	{
		if (isDirectory(res.path))
			return (handle_dir(res));
		if ((res.code = openFile(res.path)) == 404)
		{
			return (getErrorPage(res));
		}
		return setAll(res.code);
	}
}

std::string GetResponse::redirectPage(t_response res)
{
	std::string ret;
	setType();
	setCode();
	setLength();
	std::string loc = "Location :" + res.location;
	ret =  "HTTP/1.1 301\n" +loc + "\n" +_type + "\n" + _length;
	return ret;
}

int GetResponse::getName(void)
{

}

void GetResponse::setType(void)
{
	_type = _name.substr(_name.find_last_of(".") + 1);
	std::cout << _type << std::endl;
	if (_type.empty())
		_type = "html";
	_type = "Content-Type: text/" + _type;
}

void GetResponse::setLength(void)
{
	int i = _file.length();
	std::stringstream ss;
	ss << i;
	_length = "Content-Length: " + ss.str();
}

void GetResponse::setCode(void)
{
	_code = "HTTP/1.1 200 OK";
}

std::string GetResponse::getErrorPage(t_response res)
{
	int code = res.code;
	int i = 0;
	std::cout << "dans l'erreur" << std::endl;
	while (i < res.errPages.size())
	{
		if (code == res.errPages[i].first)
		{
			openFile(res.errPages[i].second);
			return (setAll(code));
		}
		i++;
	}
	openFile(_defaultError);
	return (setAll(code));
}

int GetResponse::openFile(std::string name)
{
	std::cout << "path  = |" << name << "|" <<std::endl;
	std::ostringstream buf;
	std::ifstream myfile(name, std::ifstream::in);
	if (!(myfile.is_open()))
		return 404;
	while (getline(myfile, _file))
		buf << _file;
	_file = buf.str();
	return (200);
}

int GetResponse::openFile(void)
{
	std::ostringstream buf;
	std::ifstream myfile(_name.c_str(), std::ifstream::in);
	if (!(myfile.is_open()))
		return 404;
	while (getline(myfile, _file))
		buf << _file;
	_file = buf.str();
	return (0);
}

std::string GetResponse::setAll(int code)
{
	std::string ret;
	std::string strCode = intToString(code);
	setType();
	setCode();
	setLength();
	ret =  "HTTP/1.1 " + strCode + "\n" +_type + "\n" + _length +  "\n\n" + _file;
	return ret;
}

GetResponse::GetResponse(GetResponse const &c)
{
	*this = c;
}

GetResponse &GetResponse::operator=(GetResponse const &c)
{
	return (*this);
}

GetResponse::~GetResponse()
{

}