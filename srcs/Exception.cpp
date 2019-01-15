#include "../includes/Exception.hpp"

Overflow::Overflow()
: value("0")
{}

Overflow::Overflow(std::string value)
: value(value)
{}

Overflow::Overflow(Overflow const & rv)
: value(rv.value)
{}

Overflow::~Overflow() throw()
{}

Overflow & Overflow::operator=(Overflow const & rv)
{
	if (this != &rv)
	{
		value = rv.value;
	}
	return *this;
}

const char* Overflow::what() const throw()
{
	std::string out = "\033[31mOverflow of the value: " + value + "\033[0m";
	return out.c_str();
}

const char* DivModByZero::what() const throw()
{
	return ("\033[31mDivision by zero!\033[0m");
}

const char* BadArgumentsException::what() const throw()
{
	return ("\033[31mToo much arguments.\nUsage: ./avm [file_name]\033[0m");
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
