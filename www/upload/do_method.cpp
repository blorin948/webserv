
#include "includes/Webserv.h"
#include "includes/GetResponse.hpp"
#include "includes/ParseRequest.hpp"
#include "includes/PostResponse.hpp"
#include "includes/CgiMaker.hpp"
#include "includes/DeleteRequest.hpp"
#include "includes/ServerConf.hpp"

void delete_succes_response(std::string &serv_response)
{
	serv_response.append("HTTP/1.1 200\n");
	serv_response.append("<html><body><h1>File deleted.</h1></body></html>");
}

void delete_failure_response(std::string &serv_response)
{
	serv_response.append("HTTP/1.1 404\n");
	serv_response.append("<html><body><h1>File not deleted.</h1></body></html>");
}

void do_delete(t_response &res, std::string &serv_response)
{
	DeleteRequest t;
	res = t.make_delete(res);
	if (res.code == 200)
		delete_succes_response(serv_response);
	else
		delete_failure_response(serv_response);
}

void do_cgi(t_response &res, std::string &serv_response)
{
	GetResponse t;
	if (res.code != 200)
	{
		serv_response = t.getErrorPage(res);
		return ;
	}
	serv_response = t.setAllCgi(res);
}

void do_post(t_response &res, t_request req,  std::string &serv_response, ServerConf *serv)
{
	PostResponse ok;
	if (req.size > serv->getLimit())
		res.code = 413;
	serv_response = ok.makePost(req, res);
}

void do_get(t_response t, std::string &serv_response)
{
	GetResponse ok;
	serv_response = ok.getFullResponse(t);
}

