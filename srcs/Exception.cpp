#include "../includes/Exception.hpp"

const char* Overflow::what() const throw()
{
	return ("\033[31mOverflow happened\033[0m");
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


LexerException::LexerException()
: comment("none"), line(0)
{}

LexerException::LexerException(std::string comment, int line)
: comment(comment), line(line)
{}

LexerException::LexerException(LexerException const & rv)
: comment(rv.comment), line(rv.line)
{}

LexerException::~LexerException() throw()
{}

LexerException & LexerException::operator=(LexerException const & rv)
{
	if (this != &rv)
	{
		comment = rv.comment;
		line = rv.line;
	}
	return *this;
}

const char* LexerException::what() const throw()
{
	std::string out = "\033[35mLexical error(line " + std::to_string(line) + ") : " + comment + "\033[0m";
	return out.c_str();
}
