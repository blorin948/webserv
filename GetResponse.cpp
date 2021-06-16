#include "GetResponse.hpp"

GetResponse::GetResponse(std::vector<std::string> request) : _request(request)
{
	setName();	
}

GetResponse::GetResponse(void)
{

}

void GetResponse::setName(void)
{
	int i = 4;
	while (_request[0][i] != 32)
		i++;
	this->_name = _request[0].substr(5, _request[0].find(" ", 4) - 5);
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

std::string GetResponse::getErrorPage(std::string name, std::string code)
{
	// if name = empty et code = 0 faire la page par defaut
	if (name.empty())
		name = "Default.html";
	std::string error;
	std::cout << name << "     " << code << std::endl;
	error = "HTTP/1.1 " + code + "\n";
	error.append("Content-Type: text/html\n");
	error.append("Content-Length: ");
	openFile("Error/" + name);
	setLength();
	error.append(_length);
	error.append("\n\n");
	error.append(_file);
	return (error);
}

int GetResponse::openFile(std::string name)
{
	std::ostringstream buf;
	std::ifstream myfile(name, std::ifstream::in);
	if (!(myfile.is_open()))
		return 404;
	while (getline(myfile, _file))
		buf << _file;
	_file = buf.str();
	return (0);
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

std::string GetResponse::setAll(void)
{
	std::string ret;
	openFile();
	setType();
	setCode();
	setLength();
	ret =  "HTTP/1.1 200 OK\n" +_type + "\n" + _length +  "\n\n" + _file;
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