
#include "../includes/VM.hpp"
// #include "../includes/Operand.hpp"
// #include "../includes/Factory.hpp"

std::stack<IOperand*> stack;

int main(int argc, char **argv)
{
	// VM vm;
	
	Parser p;

	if (argc == 2)
		p.read_file(argv[argc - 1]);


	// Factory f1;
	// const IOperand* io1 = f1.createOperand(Int32, "23");

	// Factory f2;
	// const IOperand* io2 = f2.createOperand(Float, "77.5");

	// try
	// {
	// 	const IOperand* io3 = *io1 + *io2;
	// 	std::cout << io3->toString() << std::endl;

	// 	const IOperand* io4 = *io1 - *io2;
	// 	std::cout << io4->toString() << std::endl;

	// 	const IOperand* io5 = *io1 * *io2;
	// 	std::cout << io5->toString() << std::endl;

	// 	const IOperand* io6 = *io1 / *io2;
	// 	std::cout << io6->toString() << std::endl;

	// 	const IOperand* io7 = *io1 % *io2;
	// 	std::cout << io7->toString() << std::endl;
	// }
	// catch(std::exception &e)
	// {
	// 	std::cout << e.what() << std::endl;
	// }
	return (0);
}
