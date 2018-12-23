
#include "../includes/Parser.hpp"

// Parser::Parser()
// {}

void Parser::print_parse_line()
{
	for (auto it = parse_line.begin(); it != parse_line.end(); ++it)
	{
		std::cout << *it << std::endl;
	}
}

void Parser::parse(std::string const & str)
{
	std::regex rule1("^(push|assert) (int8|int16|int32|float|double)\\((-?\\d+(\\.\\d+)?)\\)$");
	std::regex rule2("^(pop|dump|add|sub|mul|div|mod|print|exit)$");
	std::smatch match;

	if (std::regex_match(str, match, rule1))
	{
		std::cout << "Good string - type 1\n";

		parse_line.push_back(match.str(1));
		parse_line.push_back(match.str(2));
		parse_line.push_back(match.str(3));
		print_parse_line();
		parse_line.clear();
	}
	else if (std::regex_match(str, match, rule2))
	{
		std::cout << "Good string - type 2\n";

		parse_line.push_back(match.str(1));
		print_parse_line();
		parse_line.clear();
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
