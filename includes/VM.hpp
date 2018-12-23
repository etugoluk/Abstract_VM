
#ifndef VM_HPP
#define VM_HPP

#include "Operand.hpp"
#include "Parser.hpp"

class VM
{
	std::deque<const IOperand*> stack;
	std::vector<std::string> parse_line;

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
	// Parser p;
	void print_parse_line();
	void parse(std::string const & str);
	void read_file(std::string const & str);
	void execute();
};

#endif
