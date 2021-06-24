#ifndef UPLOAD_HPP
# define UPLOAD_HPP

#include <iostream>
#include <string>

class Upload
{

	public :

	Upload();
	Upload(Upload const &c);
	Upload &operator=(Upload const &c);
	~Upload();
	int isUpload(t_request req);

	private :



};

#endif