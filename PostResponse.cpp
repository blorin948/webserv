#include "includes/PostResponse.hpp"


PostResponse::PostResponse(void)
{

}

PostResponse::PostResponse(PostResponse const &c)
{
	*this = c;
}

PostResponse::~PostResponse()
{

}

int PostResponse::createFile(t_request req, t_response res)
{
	std::ofstream file(res.uploadPath + req.uploadName);
	if (!file.good())
		return 500;
	file << req.body;
	return (201);
}

std::string PostResponse::getHtmlPage(std::string str, t_response res)
{
	std::ostringstream ss;
	std::string path = res.uploadPath.substr(res.uploadPath.find("/"));
	ss << "<!DOCTYPE html>\n";
	ss << "<html>\n<title>404 Not Found</title>\n<body>\n<div>\n<H1>Upload Sucess ! </H1>\n<p> Pour acceder au document <a href=" + path + str + ">" + str + "</a></p>   \n</div>\n</body>\n</html>";
	return ss.str();
}

std::string PostResponse::succesUpload(int code, t_request req, t_response res)
{
	std::string file = getHtmlPage(req.uploadName, res);
	std::string ret;
	std::string strCode = intToString(code);
	ret =  "HTTP/1.1 " + strCode + "\nContent-Type: text/html\nContent-Length: " + intToString(file.length()) +  "\n\n" + file;
	return ret;
}

std::string PostResponse::makePost(t_request req, t_response res)
{
	int code = res.code;
	GetResponse t;
	if (code > 0)
		return (t.getErrorPage(res));
	if (req.isUpload == true)
	{
		if (res.can_upload == true)
			code = createFile(req, res);
		else
			res.code = 409;
	}
	if (code != 201)
		return (t.getErrorPage(res));
	return succesUpload(code, req, res);
}