#include "Webserv.h"

void initResponse(t_response &t)
{
	t.code = 0;
	t.autoindex = false;
}

void initRequest(t_request &t)
{
	t.size = 0;
	t.port = 0;
	t.code = 0;
	t.isUpload = false;
}
