#ifndef OPERAND_HPP
# define OPERAND_HPP

#include "IOperand.hpp"

template <typename T>
class Operand : public IOperand
{
    T value;
public:
	Operand();
	Operand(T value) : value(value) {}
	Operand(Operand const &o);

	Operand & operator=(Operand const &o);

	~Operand() {}
};

#endif
