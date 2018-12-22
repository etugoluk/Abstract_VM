
#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <fstream>
#include <array>
#include <regex>

class Parser
{
	std::array<std::string, 3> parse_line;
public:
	Parser();

	void print_parse_line();
	void parse(std::string const & str);
	void read_file(std::string const & str);
};

#endif
