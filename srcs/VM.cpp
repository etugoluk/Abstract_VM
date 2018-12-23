#include "../includes/VM.hpp"

void VM::Push(eOperandType type, std::string const & value)
{
	stack.push_back(f.createOperand(type, value));
}

void VM::Pop()
{
	//check empty stack
	if (stack.size() != 0)
		stack.pop_back();
}

void VM::Dump()
{
	for (auto i = stack.size(); i != 0; --i)
	{
		std::cout << stack[i] << std::endl;
	}
}

void VM::Assert(eOperandType type, std::string const & value)
{
	const IOperand* top = stack.back();

	if (type != top->getType() ||
		value.compare(top->toString()))
	{
		//error;
		std::cout << "Assert error!" << std::endl;
	}
}

void VM::Add()
{
	if (stack.size() < 2)
	{
		//error
		std::cout << "Operation error!" << std::endl;
		return ;
	}
	const IOperand* io1 = stack.back();
	stack.pop_back();
	const IOperand* io2 = stack.back();
	stack.pop_back();

	stack.push_back(*io1 + *io2);
}

void VM::Sub()
{
	if (stack.size() < 2)
	{
		//error
		std::cout << "Operation error!" << std::endl;
		return ;
	}
	const IOperand* io1 = stack.back();
	stack.pop_back();
	const IOperand* io2 = stack.back();
	stack.pop_back();

	stack.push_back(*io1 - *io2);
}

void VM::Mul()
{
	if (stack.size() < 2)
	{
		//error
		std::cout << "Operation error!" << std::endl;
		return ;
	}
	const IOperand* io1 = stack.back();
	stack.pop_back();
	const IOperand* io2 = stack.back();
	stack.pop_back();

	stack.push_back(*io1 * *io2);
}

void VM::Div()
{
	if (stack.size() < 2)
	{
		//error
		std::cout << "Operation error!" << std::endl;
		return ;
	}
	const IOperand* io1 = stack.back();
	stack.pop_back();
	const IOperand* io2 = stack.back();
	stack.pop_back();

	stack.push_back(*io1 / *io2);
}

void VM::Mod()
{
	if (stack.size() < 2)
	{
		//error
		std::cout << "Operation error!" << std::endl;
		return ;
	}
	const IOperand* io1 = stack.back();
	stack.pop_back();
	const IOperand* io2 = stack.back();
	stack.pop_back();

	stack.push_back(*io1 % *io2);
}

void VM::Print()
{
	//???
}

void VM::Exit()
{
	exit(0);
}
