#include "RouteConf.hpp"

RouteConf::RouteConf(): _sizeLimit(0), _index(false), _sizePath(0), _can_upload(false), _isCgi(false)
{
	
}

RouteConf::RouteConf(RouteConf const &c)
{
	*this = c;
}

t_response RouteConf::getReponse(t_response res, t_request req)
{
	t_response t = res;
	t.oldpath = req.path;
	if (req.code > 0)
	{
		t.code = req.code;
		t.method = "GET";
		t.errPages = _errPages;
		std::cout << "error 400" << std::endl;
		return (t);
	}
	if (_rewrite.empty() == 0)
	{
		t.code = 301;
		t.location = _rewrite;
	}
	setResMethod(t, req);
	setResPath(t, req);
	t.autoindex = _index;
	t.errPages = _errPages;
	t.maxBodySize = _sizeLimit;
	t.defaultDir = _defaultDir;
	t.uploadPath = _uploadPath;
	t.can_upload = _can_upload;
	return (t);
}

std::string RouteConf::getPath(void)
{
	return (_path);
}

void RouteConf::setResPath(t_response &t, t_request req)
{
	req.path.erase(0, 1);
	t.path = _root + req.path;
}

void RouteConf::setResMethod(t_response &t, t_request req)
{
	int i = 0;
	std::cout << _method.size() << std::endl;
	while (i < _method.size())
	{
		if (_method[i].compare(req.method) == 0)
			t.method = req.method;
		i++;
	}
	if (t.method.empty())
	{
		t.method = "GET";
		t.code = 405;
	}
}

RouteConf &RouteConf::operator=(RouteConf const &c)
{
	_sizeLimit = c._sizeLimit;
	_sizePath = c._sizePath;
	_path = c._path;
	_index = c._index;
	_method = c._method;
	_rewrite = c._rewrite;
	_defaultDir = c._defaultDir;
	_conf = c._conf;
	_servName = c._servName;
	_root = c._root;
	_port = c._port;
	_errPages = c._errPages;
	return (*this);
}

RouteConf::~RouteConf()
{

}

void RouteConf::parseCgi(std::string cgi)
{
	int i = 0;
	std::string extension;
	if ((i = _conf.find(cgi, i)) && i != std::string::npos)
	{
		if (isWord(i, cgi.length(), _conf))
		{
			i = i + cgi.length();	
			while (isspace(_conf[i]))
				i++;
			while (isspace(_conf[i]) == 0)
			{
				extension.append(1, _conf[i]);
				i++;
			}
		}
		i++;
	}
	if (extension.size() > 0)
	{
		if (extension.compare(".bla") == 0)
		{
			std::cout << "blabla" << std::endl;
			_isCgi = true;
		}
		else
			throw std::runtime_error("Server accept only .bla cgi files");
	}
}


void RouteConf::parseUpload(std::string upload)
{
	int i = 0;
	if ((i = _conf.find(upload, i)) && i != std::string::npos)
	{
		if (isWord(i, upload.length(), _conf))
		{
			i = i + upload.length();	
			while (isspace(_conf[i]))
				i++;
			while (isspace(_conf[i]) == 0)
			{
				_uploadPath.append(1, _conf[i]);
				i++;
			}
		}
		i++;
	}
	if (_uploadPath.size() > 0)
	{
		DIR *dir = opendir(_uploadPath.c_str());
		if (!(dir && _uploadPath[_uploadPath.size() - 1] == '/'))
			throw std::runtime_error("Error with upload_path");
		else
			_can_upload = true;
	}
}

std::string RouteConf::getCgiPath(void)
{
	return (_cgi_path);
}

bool RouteConf::getIsCgi(void)
{
	return (_isCgi);
}

void RouteConf::parseLocation(void)
{
	parsePath();
	parseMethod("method");
	parseRoot("root");
	parseAutoindex("autoindex");
	parseIndex("default_dir");
	parseRedirect("return");
	parseUpload("upload_path");
	parseCgi("cgi_extension");
	parseCgiPath("cgi_path");
}

void RouteConf::parseRedirect(std::string redirect)
{
	int i = 0;
	if ((i = _conf.find(redirect, i)) && i != std::string::npos)
	{
		
		if (isWord(i, redirect.length(), _conf))
		{
			i = i + redirect.length();
			while (isspace(_conf[i]) && _conf[i] != '\n')
				i++;
			while (isspace(_conf[i]) == 0)
			{
				_rewrite.append(1, _conf[i]);
				i++;
			}
		}
		i++;
		if (_rewrite.empty())
			throw std::runtime_error("Error with redirection");
		if (_rewrite.compare(0, 7,"http://") != 0 && _rewrite.compare(0, 8,"https://") != 0)
			throw std::runtime_error("Error with http redirection");
	}
}

void RouteConf::parseAutoindex(std::string autoindex)
{
	int i = 0;
	std::string index;
	if ((i = _conf.find(autoindex, i)) && i != std::string::npos)
	{
		if (isWord(i, autoindex.length(), _conf))
		{
			i = i + autoindex.length();		
			while (isspace(_conf[i]) && _conf[i] != '\n')
				i++;
			while (isspace(_conf[i]) == 0)
			{
				index.append(1, _conf[i]);
				i++;
			}
		}
		i++;
		if (index.empty())
			throw std::runtime_error("Error with autoindex");
	}
	if (index.compare("on") == 0)
		_index = true;
}


void RouteConf::parseIndex(std::string index)
{
	int i = 0;
	if ((i = _conf.find(index, i)) && i != std::string::npos)
	{
		if (isWord(i, index.length(), _conf))
		{
			i = i + index.length();	
			while (isspace(_conf[i]) && _conf[i] != '\n')
				i++;
			while (isspace(_conf[i]) == 0)
			{
				_defaultDir.append(1, _conf[i]);
				i++;
			}
		}
		i++;
		if (_defaultDir.empty())
			throw std::runtime_error("Error with default directory");
	}
}

void RouteConf::parseCgiPath(std::string cgi)
{
	int i = 0;
	if ((i = _conf.find(cgi, i)) && i != std::string::npos)
	{
		if (isWord(i, cgi.length(), _conf))
		{
			i = i + cgi.length();
			_cgi_path.clear();
			while (isspace(_conf[i]) && _conf[i] != '\n')
				i++;
			while (isspace(_conf[i]) == 0)
			{
				_cgi_path.append(1, _conf[i]);
				i++;
			}
		}
		i++;
		std::cout << _cgi_path << std::endl;
		if (_cgi_path.empty())
			throw std::runtime_error("Error with cgi path");
	}
	std::cout << _cgi_path << std::endl;
}

void RouteConf::parseRoot(std::string root)
{
	int i = 0;
	if ((i = _conf.find(root, i)) && i != std::string::npos)
	{
		_root.clear();
		if (isWord(i, root.length(), _conf))
		{
			i = i + root.length();
			while (isspace(_conf[i]) && _conf[i] != '\n')
				i++;
			while (isspace(_conf[i]) == 0)
			{
				_root.append(1, _conf[i]);
				i++;
			}
		}
		if (_root.empty())
			throw std::runtime_error("Error with root");
		i++;
	}
//	std::cout << _root << std::endl;
}

unsigned int RouteConf::getMaxBodySize(void) const
{
	return (_sizeLimit);
}

void RouteConf::parseMethod(std::string method)
{
	int i = 0;
	std::string str;
	if ((i = _conf.find(method, i)) && i != std::string::npos)
	{
		str.clear();
			if (isWord(i, method.length(), _conf))
			{
				i = i + method.length();
				while (_conf[i] != '\n')
				{
					while (isspace(_conf[i]) && _conf[i] != '\n' )
						i++;
					while (isspace(_conf[i]) == 0)
					{
						str.append(1, _conf[i]);
						i++;
					}
					_method.push_back(str);
				}
			}
			if (str.empty())
				throw std::runtime_error("Error with method");
		i++;
	}
	if (_method.empty())
	{
		_method.push_back("GET");
		_method.push_back("POST");
		_method.push_back("DELETE");
	}
	/*std::vector<std::string>::iterator it = _method.begin();
	while (it != _method.end())
		std::cout << "|" <<*it++ <<"|"<< std::endl;*/
}

void RouteConf::parsePath()
{
	int i = _conf.find("/");
	if (i > _conf.find("{"))
		throw std::runtime_error("Error with location block");
	while (isspace(_conf[i]) == 0)
	{
		_path.append(1, _conf[i]);
		i++;
	}
	i = 1;
	_sizePath++;
	while ((i = _path.find("/", i)) && i != std::string::npos)
	{
		i++;
		_sizePath++;
	}
	if (_path[_path.size() - 1] != '/')
	{
		_path.append(1, '/');
	}
/*	std::cout << _path << std::endl;
	std::cout << _sizePath << std::endl;*/
}

void RouteConf::printAll(void)
{
	std::cout << "ici la route" << std::endl;
	std::vector<int>::iterator it1 = _port.begin();
	while (it1 != _port.end())
		std::cout << *it1++ << std::endl;
	std::cout << _servName << std::endl;
	std::cout << _root << std::endl;
	std::cout << _sizeLimit << std::endl;
	std::map<int ,std::string>::iterator it = _errPages.begin();
	while (it != _errPages.end())
	{
		std::cout << it->first << "  " << it->second << std::endl;
		it++;
	}
	std::cout << _conf << std::endl;
}

void RouteConf::setRoot(std::string root)
{
	_root = root;
}

void RouteConf::setConf(std::string conf)
{
	_conf = conf;
}

void RouteConf::setName(std::string name)
{
	_servName = name;
}

void RouteConf::setPort(std::vector <int> port)
{
	_port = port;
}

void RouteConf::setErrPages(std::map <int, std::string> errPages)
{
	_errPages = errPages;
}

void RouteConf::setLimit(unsigned int sizeLimit)
{
	_sizeLimit = sizeLimit;
}

std::string RouteConf::getRoot(void) const
{
	return _root;
}

int RouteConf::getSizePath(void) const
{
	return (_sizePath);
}

std::string RouteConf::getServName(void) const
{
	return (_servName);
}

std::ostream &operator<<(std::ostream& out, RouteConf const &c)
{
	out <<  c.getSizePath();
	return (out);
}