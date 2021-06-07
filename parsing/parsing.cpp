#include "parsing.hpp"

parsing::parsing(std::string buf) : _buffer(buf)
{
	make_vector();
}

parsing::parsing(void)
{

}

void parsing::print(void)
{
	std::vector<std::string>::iterator it = _req.begin();
	while (it != _req.end())
	{
		it++;
		std::cout << "ICI = " << *it << std::endl;
	}
}

void parsing::make_vector()
{
	int i = 0;
	int o = 0;
	int a = 0;
	std::string::iterator it = _buffer.begin();
		//_req.push_back(_buffer.substr(o, i - 1));
	//std::cout << _buffer.substr(o, i - 1) << "ICICICICICICICI "<< std::endl;
		//i = _buffer.find("\n");
	std::cout << _buffer << std::endl;
	/*while ((i = _buffer.find("\n", i)) != std::string::npos)
	{
		std::cout << i << std::endl;
		_buffer.replace(i, 1, "Z");
		i = i + 1;
	}*/

	while (it != _buffer.end())
	{
		if (*it == '\n')
			_buffer.replace(_buffer.begin() + i,_buffer.begin() + i + 1 ,"Z", 1);//std::cout<< "LALALLA =" << std::endl;
		it++;
		i++;
	}
	it = _buffer.begin();
	//std::cout << "TEST\n" ;
	std::cout << "ICI = \n" ;
	while (it != _buffer.end())
	{
		std::cout << *it;
		it++;
	}
	std::cout << std::endl;
	//std::cout << _buffer.length() << std::endl;
	//print();
}

parsing::parsing(parsing const &c)
{
	*this = c;
}

parsing &parsing::operator=(parsing const &c)
{
	return (*this);
}

parsing::~parsing()
{

}