#include "../includes/VM.hpp"
#include <sys/stat.h>
#include <unistd.h>

void VM::parser(std::string const & str, int line)
{
	try
	{
		Lexer l(str, line);
		l.check_lexer();

		std::smatch match;
		std::regex rule1("^(push|assert|asserttype|more|less) (int8|int16|int32|float|double)\\((-?\\d+(\\.\\d+)?)\\)((\\s)*;.*)*$");
		std::regex rule2("^(pop|dump|add|sub|mul|div|mod|print|exit)((\\s)*;.*)*$");

		if (std::regex_match(str, match, rule1))
		{
			parse_line.push_back(match.str(1));
			parse_line.push_back(match.str(2));
			parse_line.push_back(match.str(3));
		}
		else if (std::regex_match(str, match, rule2))
		{
			parse_line.push_back(match.str(1));
		}

		execute();
		parse_line.clear();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		parse_line.clear();
	}
}

void VM::read_console()
{
	std::vector<std::string> v;
	std::string line;

	while (std::getline(std::cin, line))
	{
		if (line[0] == ';' && line[1] == ';')
			break;
		v.push_back(line);
	}

	int count = 1;
	for (auto it = v.begin(); it != v.end(); ++it)
	{
		if (!it->size() || (*it)[0] == ';')
			++count;
		else
			parser(*it, count++);
	}
	throw NoExit();
}

void VM::read_file(std::string const & str)
{
	struct stat status;

	if (stat(str.c_str(), &status) == -1)
		throw BadFileException(str + ": No such file or directory");
	else if (S_ISDIR(status.st_mode))
		throw BadFileException(str + ": is a directory");
	else if (access(str.c_str(), R_OK) == -1)
		throw BadFileException(str + ": Permission denied");

	std::ifstream in(str);
	std::string line;
	int			count = 1;

	while (std::getline(in, line))
	{
		if (!line.size() || line[0] == ';')
		{
			++count;
			continue ;
		}
		parser(line, count++);
	}
	throw NoExit();
}

void VM::execute()
{
	if (parse_line.size() == 3)
	{
		eOperandType e;
		if (!parse_line[1].compare("int8"))
			e = Int8;
		else if (!parse_line[1].compare("int16"))
			e = Int16;
		else if (!parse_line[1].compare("int32"))
			e = Int32;
		else if (!parse_line[1].compare("double"))
			e = Double;
		else if (!parse_line[1].compare("float"))
			e = Float;
		if (!parse_line[0].compare("push"))
			Push(e, parse_line[2]);
		else if (!parse_line[0].compare("assert"))
			Assert(e, parse_line[2]);
		else if (!parse_line[0].compare("asserttype"))
			AssertType(e, parse_line[2]);
		else if (!parse_line[0].compare("more"))
			More(e, parse_line[2]);
		else if (!parse_line[0].compare("less"))
			Less(e, parse_line[2]);
	}
	else if (parse_line.size() == 1)
	{
		if (!parse_line[0].compare("pop"))
			Pop();
		else if (!parse_line[0].compare("dump"))
			Dump();
		else if (!parse_line[0].compare("add"))
			Add();
		else if (!parse_line[0].compare("sub"))
			Sub();
		else if (!parse_line[0].compare("mul"))
			Mul();
		else if (!parse_line[0].compare("div"))
			Div();
		else if (!parse_line[0].compare("mod"))
			Mod();
		else if (!parse_line[0].compare("print"))
			Print();
		else if (!parse_line[0].compare("exit"))
			Exit();
	}
}

void VM::Push(eOperandType type, std::string const & value)
{
	stack.push_back(f.createOperand(type, value));
}

void VM::Pop()
{
	if (!stack.size())
		throw SmallStack("Instruction pop on an empty stack");

	delete stack.back();
	stack.pop_back();
}

void VM::Dump()
{
	for (int i = stack.size() - 1; i != -1; --i)
	{
		std::cout << stack[i]->toString() << std::endl;
	}
}

void VM::Assert(eOperandType type, std::string const & value)
{
	if (!stack.size())
		throw SmallStack("Instruction assert on an empty stack");

	const IOperand* top = stack.back();
	const IOperand* arg = Factory().createOperand(type, value);

	if (arg->toString().compare(top->toString()))
		throw AssertException("An assert instruction is not true");

	delete arg;

	std::cout << "\033[32mAn assert instruction is true\033[0m" << std::endl;
}

void VM::Add()
{
	if (stack.size() < 2)
		throw SmallStack("Instruction add on strictly less that two values stack");
	const IOperand* io1 = stack.back();
	stack.pop_back();
	const IOperand* io2 = stack.back();
	stack.pop_back();

	stack.push_back(*io1 + *io2);

	delete io1;
	delete io2;
}

void VM::Sub()
{
	if (stack.size() < 2)
		throw SmallStack("Instruction sub on strictly less that two values stack");
	const IOperand* io1 = stack.back();
	stack.pop_back();
	const IOperand* io2 = stack.back();
	stack.pop_back();

	stack.push_back(*io2 - *io1);

	delete io1;
	delete io2;
}

void VM::Mul()
{
	if (stack.size() < 2)
		throw SmallStack("Instruction mul on strictly less that two values stack");
	const IOperand* io1 = stack.back();
	stack.pop_back();
	const IOperand* io2 = stack.back();
	stack.pop_back();

	stack.push_back(*io1 * *io2);

	delete io1;
	delete io2;
}

void VM::Div()
{
	if (stack.size() < 2)
		throw SmallStack("Instruction div on strictly less that two values stack");
	const IOperand* io1 = stack.back();
	stack.pop_back();
	const IOperand* io2 = stack.back();
	stack.pop_back();

	stack.push_back(*io2 / *io1);

	delete io1;
	delete io2;
}

void VM::Mod()
{
	if (stack.size() < 2)
		throw SmallStack("Instruction mod on strictly less that two values stack");
	const IOperand* io1 = stack.back();
	stack.pop_back();
	const IOperand* io2 = stack.back();
	stack.pop_back();

	stack.push_back(*io2 % *io1);

	delete io1;
	delete io2;
}

void VM::Print()
{
	const IOperand* top = stack.back();

	if (top->getType())
		throw PrintException();
	std::cout << static_cast<char>(std::stoi(top->toString())) << std::endl;
}

void VM::Exit()
{
	// system("leaks avm");
	exit(0);
}

void VM::AssertType(eOperandType type, std::string const & value)
{
	if (!stack.size())
		throw SmallStack("Instruction asserttype on an empty stack");

	const IOperand* top = stack.back();
	const IOperand* arg = Factory().createOperand(type, value);

	if (arg->getType() != top->getType())
		throw AssertException("An asserttype instruction is not true");

	delete arg;

	std::cout << "\033[32mAn asserttype instruction is true\033[0m" << std::endl;
}

void VM::More(eOperandType type, std::string const & value)
{
	if (!stack.size())
		throw SmallStack("Instruction more on an empty stack");

	const IOperand* top = stack.back();
	const IOperand* arg = Factory().createOperand(type, value);

	if (arg->toString().compare(top->toString()) <= 0)
		throw AssertException("A more instruction is not true");

	delete arg;

	std::cout << "\033[32mA more instruction is true\033[0m" << std::endl;
}

void VM::Less(eOperandType type, std::string const & value)
{
	if (!stack.size())
		throw SmallStack("Instruction less on an empty stack");

	const IOperand* top = stack.back();
	const IOperand* arg = Factory().createOperand(type, value);

	if (arg->toString().compare(top->toString()) >= 0)
		throw AssertException("A less instruction is not true");

	delete arg;

	std::cout << "\033[32mA less instruction is true\033[0m" << std::endl;
}

VM::SmallStack::SmallStack()
: comment("none")
{}

VM::SmallStack::SmallStack(std::string comment)
: comment(comment)
{}

VM::SmallStack::SmallStack(SmallStack const & rv)
: comment(rv.comment)
{}

VM::SmallStack::~SmallStack() throw()
{}

VM::SmallStack & VM::SmallStack::operator=(VM::SmallStack const & rv)
{
	if (this != &rv)
	{
		comment = rv.comment;
	}
	return *this;
}

const char* VM::SmallStack::what() const throw()
{
	std::string out = "\033[31m" + comment + "\033[0m";
	return out.c_str();
}

const char* VM::NoExit::what() const throw()
{
	return ("\033[31mNo exit command\033[0m");
}

VM::AssertException::AssertException()
: comment("none")
{}

VM::AssertException::AssertException(std::string comment)
: comment(comment)
{}

VM::AssertException::AssertException(AssertException const & rv)
: comment(rv.comment)
{}

VM::AssertException::~AssertException() throw()
{}

VM::AssertException & VM::AssertException::operator=(VM::AssertException const & rv)
{
	if (this != &rv)
	{
		comment = rv.comment;
	}
	return *this;
}

const char* VM::AssertException::what() const throw()
{
	std::string out = "\033[31m" + comment + "\033[0m";
	return out.c_str();
}

const char* VM::PrintException::what() const throw()
{
	return ("\033[31mValue is not a 8-bit integer\033[0m");
}
