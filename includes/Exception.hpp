#ifndef EXCEPTION_HPP
# define EXCEPTION_HPP

#include <iostream>

class Overflow : public std::exception
{
public:
	virtual const char *what() const throw();
};

class DivModByZero : public std::exception
{
public:
	virtual const char *what() const throw();
};

class BadArgumentsException : public std::exception
{
public:
	virtual const char *what() const throw();
};

class BadFileException : public std::exception
{
	std::string comment;
public:
	BadFileException();
	BadFileException(std::string comment);
	BadFileException(BadFileException const & rv);
	~BadFileException() throw();
	
	BadFileException & operator=(BadFileException const & rv);

	virtual const char *what() const throw();
};

#endif