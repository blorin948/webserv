#include "includes/DeleteRequest.hpp"

t_response DeleteRequest::make_delete(t_response res)
{
	int i = 0;
	i = remove(res.path.c_str());
	if (i != 0)
		res.code = 404;
	else
		res.code = 200;
	return (res);
}


DeleteRequest::DeleteRequest(void)
{

}

DeleteRequest::DeleteRequest(DeleteRequest const &c)
{
	*this = c;
}

DeleteRequest::~DeleteRequest()
{

}