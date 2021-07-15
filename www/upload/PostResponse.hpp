
#ifndef POSTRESPONSE_HPP
# define POSTRESPONSE_HPP

#include <iostream>
#include <string>
#include "Webserv.h"
#include "GetResponse.hpp"

class PostResponse
{

	public :

	PostResponse();
	PostResponse(PostResponse const &c);
	PostResponse &operator=(PostResponse const &c);
	~PostResponse();
	std::string makePost(t_request req, t_response res);
	int createFile(t_request req, t_response res);
	std::string succesUpload(int code, t_request req, t_response res);

	private :

	std::string getHtmlPage(std::string str, t_response res);
};

#endif
-----------------------------29901068824793174311361009471
Content-Disposition: form-data; name="submit"

Upload
-----------------------------29901068824793174311361009471--
