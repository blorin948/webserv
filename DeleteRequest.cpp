#include "DeleteRequest.hpp"

t_response DeleteRequest::make_delete(t_request req, t_response res)
{
	int i = 0;
	i = remove(res.path.c_str());
	if (i != 0)
	{
		res.code = 404;
	}
	else
		res.code = 200;
	std::cout << "test" << std::endl;
	return (res);
}


DeleteRequest::DeleteRequest(void)
{

}

DeleteRequest::DeleteRequest(DeleteRequest const &c)
{
	*this = c;
}

DeleteRequest &DeleteRequest::operator=(DeleteRequest const &c)
{
	return (*this);
}

DeleteRequest::~DeleteRequest()
{

}