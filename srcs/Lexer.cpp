#include "../includes/Lexer.hpp"

Lexer::Lexer() : str(""), line(0)
{}

Lexer::Lexer(std::string const & str, int line) : str(str), line(line)
{}

Lexer::Lexer(Lexer const & rv) : str(rv.str), line(rv.line)
{}

Lexer::~Lexer()
{}

Lexer & Lexer::operator=(Lexer const & rv)
{
	if (this != &rv)
	{
		match = rv.match;
		str = rv.str;
		line = rv.line;
	}
	return *this;
}

bool Lexer::is_command1()
{
	std::regex reg("(.)*(push|assert|asserttype|more|less)(.)*");

	if (!std::regex_match(str, match, reg))
		return false;
	return true;
}

bool Lexer::is_command2()
{
	std::regex reg("(.)*(pop|dump|add|sub|mul|div|mod|print|exit)(.)*");

	if (!std::regex_match(str, match, reg))
		return false;
	return true;
}

bool Lexer::command_on_the_begin()
{
	std::regex reg("^(push|assert|pop|dump|add|sub|mul|div|mod|print|exit|asserttype|more|less)(.)*");

	if (!std::regex_match(str, match, reg))
		return false;
	return true;
}

bool Lexer::is_arg()
{
	std::regex reg("^(push|assert|asserttype|more|less)(\\s)+(int8|int16|int32|float|double)\\((-?\\d+(\\.\\d+)?)\\)(.)*$");

	if (!std::regex_match(str, match, reg))
		return false;
	return true;
}

bool Lexer::is_space()
{
	std::regex reg("^(push|assert|asserttype|more|less) (int8|int16|int32|float|double)\\((-?\\d+(\\.\\d+)?)\\)(.)*$");

	if (!std::regex_match(str, match, reg))
		return false;
	return true;
}

bool Lexer::good_command()
{
	std::regex rule1("^(push|assert|asserttype|more|less) (int8|int16|int32|float|double)\\((-?\\d+(\\.\\d+)?)\\)((\\s)*;.*)*$");
	std::regex rule2("^(pop|dump|add|sub|mul|div|mod|print|exit)((\\s)*;.*)*$");

	std::regex is_integer_type("(int8|int16|int32)");
	std::regex is_decimal_type("(float|double)");
	std::regex is_integer("(-?\\d+)");
	std::regex is_decimal("(-?\\d+\\.\\d+)");

	if (std::regex_match(str, match, rule1))
	{
		std::string cmnd = match.str(1);
		std::string type = match.str(2);
		std::string val = match.str(3);

		if (std::regex_match(type, match, is_integer_type) && std::regex_match(val, match, is_decimal))
			throw LexerException("Argument should be integer.", line);
		if (std::regex_match(type, match, is_decimal_type) && std::regex_match(val, match, is_integer))
			throw LexerException("Argument should be decimal.", line);
		return true;
	}
	else if (std::regex_match(str, match, rule2))
		return true;
	else
		return false;
}

void Lexer::check_lexer()
{
	if (!is_command1() && !is_command2())
		throw LexerException("Unknown instruction.", line);
	if (!command_on_the_begin())
		throw LexerException("Command should be write from the begin of the line.", line);
	if (is_command1() && !is_arg())
		throw LexerException("Bad arguments.", line);
	if (is_command1() && !is_space())
		throw LexerException("Between command and argument should be only one space.", line);
	if (!good_command())
		throw LexerException("Bad text after command.", line);
}

Lexer::LexerException::LexerException()
: comment("none"), line(0)
{}

Lexer::LexerException::LexerException(std::string comment, int line)
: comment(comment), line(line)
{}

Lexer::LexerException::LexerException(Lexer::LexerException const & rv)
: comment(rv.comment), line(rv.line)
{}

Lexer::LexerException::~LexerException() throw()
{}

Lexer::LexerException & Lexer::LexerException::operator=(Lexer::LexerException const & rv)
{
	if (this != &rv)
	{
		comment = rv.comment;
		line = rv.line;
	}
	return *this;
}

const char* Lexer::LexerException::what() const throw()
{
	std::string out = "\033[35mLexical error(line " + std::to_string(line) + ") : " + comment + "\033[0m";
	return out.c_str();
}