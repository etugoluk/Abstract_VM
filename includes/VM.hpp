
#ifndef VM_HPP
#define VM_HPP

#include "Operand.hpp"
#include "Parser.hpp"

class VM
{
	std::stack<IOperand*> stack;
public:
	void push(eOperandType type, std::string const & value);
	void pop();
	void dump(eOperandType type, std::string const & value);
	void add();
	void sub();
	void mul();
	void div();
	void mod();
	void print();
	void exit();

	Factory f;
	Parser p;
};

#endif
