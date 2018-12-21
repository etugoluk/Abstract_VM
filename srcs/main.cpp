
#include "../includes/VM.hpp"
#include "../includes/Operand.hpp"
#include "../includes/Factory.hpp"

std::stack<IOperand*> stack;

int main()
{
	Factory f;
	f.createOperand(Int8, "32");
    return (0);
}
