//
// Created by Evgenia TUGOLUKOVA on 20/12/2018.
//

#include <iostream>
#include <fstream>
#include "Parser.hpp"

void    ft_read(int argc, char **argv)
{
    std::ifstream is;
    std::string    str;

    if (argc == 2)
        is.open(argv[1]);
    while (std::getline(is, str))
    {
        Parser::parse(str);
    }
}
