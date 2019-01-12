#include "../includes/VM.hpp"

void VM::print_parse_line()
{
	for (auto it = parse_line.begin(); it != parse_line.end(); ++it)
	{
		std::cout << *it << std::endl;
	}
}

void VM::parse(std::string const & str, int line)
{
	std::regex rule1("^(push|assert) (int8|int16|int32|float|double)\\((-?\\d+(\\.\\d+)?)\\)(\\s)*(;.*)*$");
	std::regex rule2("^(pop|dump|add|sub|mul|div|mod|print|exit)(\\s)*(;.*)*$");
	std::smatch match;

	if (std::regex_match(str, match, rule1))
	{
		// std::cout << "Good string - type 1\n";

		parse_line.push_back(match.str(1));
		parse_line.push_back(match.str(2));
		parse_line.push_back(match.str(3));
		// print_parse_line();
	}
	else if (std::regex_match(str, match, rule2))
	{
		// std::cout << "Good string - type 2\n";

		parse_line.push_back(match.str(1));
	}
	else
	{
		// std::cout << "Bad string\n";
		throw UnknownInstruction(str, line);
		return ;
	}

	execute();
	parse_line.clear();
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
		parse(*it, count++);
	}
}

void VM::read_file(std::string const & str)
{
	std::ifstream in(str);
	if (!in.is_open())
		return ;

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
		else
			Assert(e, parse_line[2]);
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
		{
			Exit();
		}
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
	const IOperand* top = stack.back();
	const IOperand* arg = Factory().createOperand(type, value);

	// if (arg->getType() != top->getType() ||
	if (arg->toString().compare(top->toString()))
		throw AssertException();

	delete arg;
}

void VM::Add()
{
	if (stack.size() < 2)
		throw SmallStack("Instruction Add on strictly less that two values stack");
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
		throw SmallStack("Instruction Sub on strictly less that two values stack");
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
		throw SmallStack("Instruction Mul on strictly less that two values stack");
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
		throw SmallStack("Instruction Div on strictly less that two values stack");
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
		throw SmallStack("Instruction Mod on strictly less that two values stack");
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
		throw AssertException();
	std::cout << static_cast<char>(std::stoi(top->toString())) << std::endl;
}

void VM::Exit()
{
	// system("leaks avm");
	exit(0);
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
	std::string out = "Unknown instruction \"" + command + "\" on the line " + std::to_string(line);
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
	return comment.c_str();
}

const char* VM::NoExit::what() const throw()
{
	return ("No exit command");
}

const char* VM::AssertException::what() const throw()
{
	return ("An Assert instruction is not true");
}
