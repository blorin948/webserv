#ifndef DELETEREQUEST_HPP
# define DELETEREQUEST_HPP
#include "Webserv.h"
#include <iostream>
#include <string>

class DeleteRequest
{

	public :

	DeleteRequest();
	t_response make_delete(t_response res);
	DeleteRequest(DeleteRequest const &c);
	~DeleteRequest();

	private :

};

#endif