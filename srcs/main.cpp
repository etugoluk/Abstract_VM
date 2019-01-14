
#include "../includes/VM.hpp"
// #include "../includes/Operand.hpp"
// #include "../includes/Factory.hpp"

int main(int argc, char **argv)
{
	try
	{
		VM vm;

		if (argc == 1)
			vm.read_console();
		else if (argc == 2)
			vm.read_file(argv[1]);
		else
		{
			throw VM::BadArgumentsException();
		}
		// else
		// {
		// 	for (int i = 1; i < argc; ++i)
		// 	{
		// 		vm.read_file(argv[i]);
		// 	}
		// }
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}
