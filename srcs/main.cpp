
#include "../includes/VM.hpp"

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
			throw BadArgumentsException();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}
