
#ifndef VM_HPP
#define VM_HPP

#include "Operand.hpp"
#include "Lexer.hpp"
#include <vector>
#include <regex>
#include <fstream>

class VM
{
	std::deque<const IOperand*> stack;
	std::vector<std::string> parse_line;
	Factory	f;

public:

	VM();
	VM(VM const & rv);
	~VM();
	
	VM & operator=(VM const & rv);

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
	void AssertType(eOperandType type, std::string const & value);
	void More(eOperandType type, std::string const & value);
	void Less(eOperandType type, std::string const & value);
	void Equal(eOperandType type, std::string const & value);
	void NotEqual(eOperandType type, std::string const & value);
	void MoreEqual(eOperandType type, std::string const & value);
	void LessEqual(eOperandType type, std::string const & value);

	void parser(std::string const & str, int line);
	void read_console();
	void read_file(std::string const & str);

	void execute();

	class SmallStack : public std::exception
	{
		std::string comment;
	public:
		SmallStack();
		SmallStack(std::string comment);
		SmallStack(SmallStack const & rv);
		~SmallStack() throw();
		
		SmallStack & operator=(SmallStack const & rv);

		virtual const char *what() const throw();
	};

	class NoExit : public std::exception
	{
	public:
		virtual const char *what() const throw();
	};

	class AssertException : public std::exception
	{
		std::string comment;
	public:
		AssertException();
		AssertException(std::string comment);
		AssertException(AssertException const & rv);
		~AssertException() throw();
		
		AssertException & operator=(AssertException const & rv);

		virtual const char *what() const throw();
	};

	class PrintException : public std::exception
	{
	public:
		virtual const char *what() const throw();
	};

};

#endif
