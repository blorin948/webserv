#ifndef GETREQUEST_HPP
# define GETREQUEST_HPP

#include <iostream>
#include <string>

class GetRequest
{

	public :

	GetRequest(std::string buf);
	GetRequest(GetRequest const &c);
	GetRequest &operator=(GetRequest const &c);
	~GetRequest();

	private :

	GetRequest();
	std::string _buffer;
};

#endif