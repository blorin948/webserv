#ifndef PARSING_HPP
# define PARSING_HPP

#include <iostream>
#include <string>
#include <vector>

class parsing
{

	public :

	parsing(std::string buf);
	parsing(parsing const &c);
	parsing &operator=(parsing const &c);
	void make_vector(void);
	~parsing();

	private :
	parsing();
	void print();
	std::string _buffer;
	std::vector<std::string> _req;

};

#endif