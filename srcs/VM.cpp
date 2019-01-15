#include "../includes/VM.hpp"
#include <sys/stat.h>
#include <unistd.h>

// void VM::print_parse_line()
// {
// 	for (auto it = parse_line.begin(); it != parse_line.end(); ++it)
// 	{
// 		std::cout << *it << std::endl;
// 	}
// }

void VM::parse(std::string const & str, int line)
{
	try
	{
		std::smatch match;

		std::regex is_cmnd1("(.)*(push|assert|asserttype|more|less)(.)*");
		std::regex is_cmnd2("(.)*(pop|dump|add|sub|mul|div|mod|print|exit)(.)*");
		std::regex cmnd_begin_line("^(push|assert|pop|dump|add|sub|mul|div|mod|print|exit|asserttype|more|less)(.)*");
		std::regex is_arg("^(push|assert|asserttype|more|less)(\\s)+(int8|int16|int32|float|double)\\((-?\\d+(\\.\\d+)?)\\)(.)*$");
		std::regex is_space("^(push|assert|asserttype|more|less) (int8|int16|int32|float|double)\\((-?\\d+(\\.\\d+)?)\\)(.)*$");

		if (!std::regex_match(str, match, is_cmnd1) && !std::regex_match(str, match, is_cmnd2))
			throw UnknownInstruction(str, line);
		if (!std::regex_match(str, match, cmnd_begin_line))
			throw LexerException("Command should be write from the begin of the line.", line); //better
		if (std::regex_match(str, match, is_cmnd1) && !std::regex_match(str, match, is_arg))
			throw LexerException("Bad arguments.", line);
		if (std::regex_match(str, match, is_cmnd1) && !std::regex_match(str, match, is_space))
			throw LexerException("Between command and argument should be only one space.", line);

		std::regex rule1("^(push|assert|asserttype|more|less) (int8|int16|int32|float|double)\\((-?\\d+(\\.\\d+)?)\\)((\\s)*;.*)*$");
		std::regex rule2("^(pop|dump|add|sub|mul|div|mod|print|exit)((\\s)*;.*)*$");

		std::regex is_integer_type("(int8|int16|int32)");
		std::regex is_decimal_type("(float|double)");
		std::regex is_integer("(-?\\d+)");
		std::regex is_decimal("(-?\\d+\\.\\d+)");

		if (std::regex_match(str, match, rule1))
		{
			std::string cmnd = match.str(1);
			std::string type = match.str(2);
			std::string val = match.str(3);

			if (std::regex_match(type, match, is_integer_type) && std::regex_match(val, match, is_decimal))
				throw LexerException("Argument should be integer.", line);
			if (std::regex_match(type, match, is_decimal_type) && std::regex_match(val, match, is_integer))
				throw LexerException("Argument should be decimal.", line);

			parse_line.push_back(cmnd);
			parse_line.push_back(type);
			parse_line.push_back(val);
			// print_parse_line();
		}
		else if (std::regex_match(str, match, rule2))
		{
			parse_line.push_back(match.str(1));
		}
		else
			throw LexerException("Bad text after command.", line);

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
			parse(*it, count++);
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
		parse(line, count++);
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

	// const IOperand* top = stack.back();
	// stack.pop_back();

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

	// if (arg->getType() != top->getType() ||
	if (arg->toString().compare(top->toString()))
		throw AssertException();

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
		throw PrintException(); //need print exception
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
		throw AssertException();

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
		throw AssertException();

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
		throw AssertException();

	delete arg;

	std::cout << "\033[32mA less instruction is true\033[0m" << std::endl;
}


VM::UnknownInstruction::UnknownInstruction()
: command("none"), line(0)
{}

VM::UnknownInstruction::UnknownInstruction(std::string command, int line)
: command(command), line(line)
{}

VM::UnknownInstruction::UnknownInstruction(UnknownInstruction const & rv)
: command(rv.command), line(rv.line)
{}

VM::UnknownInstruction::~UnknownInstruction() throw()
{}

VM::UnknownInstruction & VM::UnknownInstruction::operator=(VM::UnknownInstruction const & rv)
{
	if (this != &rv)
	{
		command = rv.command;
		line = rv.line;
	}
	return *this;
}

const char* VM::UnknownInstruction::what() const throw()
{
	std::string out = "\033[31mUnknown instruction (line "+ std::to_string(line) + ") : \"" + command + "\"\033[0m";
	return out.c_str();
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

const char* VM::AssertException::what() const throw()
{
	return ("\033[31mAn assert instruction is not true\033[0m");
}

const char* VM::PrintException::what() const throw()
{
	return ("\033[31mValue is not a 8-bit integer\033[0m");
}