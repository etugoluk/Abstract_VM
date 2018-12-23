
#ifndef VM_HPP
#define VM_HPP

#include "Operand.hpp"
#include "Parser.hpp"

class VM
{
	std::deque<const IOperand*> stack;
public:
	void Push(eOperandType type, std::string const & value);
	void Pop();
	void Dump();
	void Assert(eOperandType type, std::string const & value);
	void Add();
	void Sub();
	void Mul();
	void Div();
	void Mod();
	void Print();
	void Exit();

	Factory f;
	Parser p;
};

#endif
