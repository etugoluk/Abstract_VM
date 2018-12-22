//
// Created by Evgenia TUGOLUKOVA on 20/12/2018.
//

#ifndef PARSER_HPP
#define PARSER_HPP

#include <fstream>
#include <array>
#include <regex>

class Parser
{
	std::array<std::string, 3> parse_line;
public:
	Parser() {}

	void parse(std::string const & str)
	{
		if (std::regex_match (str, std::regex("^(push|assert) (int8|int16|int32|float|double)\\(-?\\d+(\\.\\d+)?\\)")))
			std::cout << "Good string\n";
		else
			std::cout << "Bad string\n";
	}

	void read_file(std::string const & str)
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
};

#endif
