#include "../includes/Exception.hpp"

const char* Overflow::what() const throw()
{
	return ("Overflow exception");
}

const char* DivModByZero::what() const throw()
{
	return ("Division by zero!");
}

const char* BadArgumentsException::what() const throw()
{
	return ("Too much arguments.\nUsage: ./avm [file_name]");
}

BadFileException::BadFileException()
: comment("none")
{}

BadFileException::BadFileException(std::string comment)
: comment(comment)
{}

BadFileException::BadFileException(BadFileException const & rv)
: comment(rv.comment)
{}

BadFileException::~BadFileException() throw()
{}

BadFileException & BadFileException::operator=(BadFileException const & rv)
{
	if (this != &rv)
	{
		comment = rv.comment;
	}
	return *this;
}

const char* BadFileException::what() const throw()
{
	std::string out = comment + "\n" + "Usage: ./avm [file_name]";
	return out.c_str();
}
