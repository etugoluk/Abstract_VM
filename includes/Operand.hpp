#ifndef OPERAND_HPP
# define OPERAND_HPP

#include "Factory.hpp"

template <class T>
class Operand : public IOperand
{
	T				value;
	std::string		value_str;
	eOperandType	type;

public:
	Operand();
	Operand(T value, eOperandType type, std::string const & str)
	: value(value), value_str(str), type(type) {}
	Operand(Operand const &o);
	Operand & operator=(Operand const &o);
	~Operand() {}

	int getPrecision( void ) const
	{
		return type;
	} // Precision of the type of the instance

	eOperandType getType( void ) const
	{
		return type;
	} // Type of the instance

	IOperand const * operator+( IOperand const & rhs ) const
	{
		eOperandType max_type = std::max(this->getType(), rhs.getType());
		double result = std::stod(this->toString()) + std::stod(rhs.toString());
		return Factory().createOperand(max_type, std::to_string(result));
	}
	 // Sum
	IOperand const * operator-( IOperand const & rhs ) const
	{
		eOperandType max_type = std::max(this->getType(), rhs.getType());
		double result = std::stod(this->toString()) - std::stod(rhs.toString());
		return Factory().createOperand(max_type, std::to_string(result));
	}
	 // Difference
	IOperand const * operator*( IOperand const & rhs ) const
	{
		eOperandType max_type = std::max(this->getType(), rhs.getType());
		double result = std::stod(this->toString()) * std::stod(rhs.toString());
		return Factory().createOperand(max_type, std::to_string(result));
	}
	 // Product
	IOperand const * operator/( IOperand const & rhs ) const
	{
		double znam = std::stod(rhs.toString());
		if (!znam)
			throw DivModByZero();
		eOperandType max_type = std::max(this->getType(), rhs.getType());
		double result = std::stod(this->toString()) / znam;
		return Factory().createOperand(max_type, std::to_string(result));
	}
	 // Quotient
	IOperand const * operator%( IOperand const & rhs ) const
	{
		eOperandType max_type = std::max(this->getType(), rhs.getType());
		if (max_type > 2)
			throw std::invalid_argument("bad type");
		int znam = std::stoi(rhs.toString());
		if (!znam)
			throw DivModByZero();
		int result = std::stoi(this->toString()) % std::stoi(rhs.toString());
		return Factory().createOperand(max_type, std::to_string(result));
	}
	 // Modulo
	std::string const & toString(void) const // String representation of the instance
	{
		return value_str;
	}

	class DivModByZero : public std::exception
	{
	public:
		virtual const char *what() const throw()
		{
			return ("Division by zero!");
		}
	};
};

#endif
