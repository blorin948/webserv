#include "GetRequest.hpp"

GetRequest::GetRequest(std::string buf) : _buffer(buf)
{
	
}

GetRequest::GetRequest(void)
{

}

GetRequest::GetRequest(GetRequest const &c)
{
	*this = c;
}

GetRequest &GetRequest::operator=(GetRequest const &c)
{
	return (*this);
}

GetRequest::~GetRequest()
{

}