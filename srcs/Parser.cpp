
#include "../includes/Parser.hpp"

Parser::Parser()
{}

void Parser::print_parse_line()
{
	for (int i = 0; i < 3; ++i)
	{
		std::cout << parse_line[i] << std::endl;
	}
}

void Parser::parse(std::string const & str)
{
	std::regex rule("^(push|assert) (int8|int16|int32|float|double)\\((-?\\d+(\\.\\d+)?)\\)");
	std::smatch match;

	if (std::regex_match(str, match, rule))
	{
		std::cout << "Good string\n";

		parse_line[0] = match.str(1);
		parse_line[1] = match.str(2);
		parse_line[2] = match.str(3);
		print_parse_line();
	}
	else
		std::cout << "Bad string\n";
}

void Parser::read_file(std::string const & str)
{
	std::ifstream in(str);
	if (!in.is_open())
		return ;

	std::string line;
	while (std::getline(in, line))
	{
		parse(line);
	}
}
