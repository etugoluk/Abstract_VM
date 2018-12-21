#ifndef OPERAND_HPP
# define OPERAND_HPP

#include "VM.hpp"
#include "Factory.hpp"

template <typename T>
class Operand : public IOperand
{
	T				value;
	std::string		value_str;
	eOperandType	type;

public:
	Operand();
	Operand(T value, std::string str, eOperandType type)
	: value(value), value_str(str), type(type) {}
	Operand(Operand const &o);
	Operand & operator=(Operand const &o);
	~Operand() {}

	// virtual int getPrecision( void ) const = 0; // Precision of the type of the instance

	eOperandType getType( void ) const
	{
		return type;
	} // Type of the instance

	IOperand const * operator+( IOperand const & rhs ) const
	{
		T result = this->value + static_cast<T>(std::stod(rhs.toString()));
		return Factory().createOperand(type, std::to_string(result));
	}
	 // Sum
	IOperand const * operator-( IOperand const & rhs ) const
	{
		T result = this->value - static_cast<T>(std::stod(rhs.toString()));
		return Factory().createOperand(type, std::to_string(result));
	}
	 // Difference
	IOperand const * operator*( IOperand const & rhs ) const
	{
		T result = this->value * static_cast<T>(std::stod(rhs.toString()));
		return Factory().createOperand(type, std::to_string(result));
	}
	 // Product
	IOperand const * operator/( IOperand const & rhs ) const
	{
		T result = this->value / static_cast<T>(std::stod(rhs.toString()));
		return Factory().createOperand(type, std::to_string(result));
	}
	 // Quotient
	IOperand const * operator%( IOperand const & rhs ) const
	{
		T result = static_cast<int>(this->value) % static_cast<int>(std::stoi(rhs.toString()));
		return Factory().createOperand(type, std::to_string(result));
	}
	 // Modulo
	std::string const & toString(void) const // String representation of the instance
	{
		return value_str;
	}
};

#endif
