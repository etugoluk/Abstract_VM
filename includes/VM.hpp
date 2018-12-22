
#ifndef VM_HPP
#define VM_HPP

#include "Operand.hpp"
#include "Parser.hpp"

class VM
{
	Factory f;
	Parser p;
	std::stack<IOperand*> stack;
};

#endif
