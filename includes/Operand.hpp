#ifndef OPERAND_HPP
# define OPERAND_HPP

#include "Factory.hpp"
#include <sstream>

template <class T>
class Operand : public IOperand
{
	T				value;
	std::string		value_str;
	eOperandType	type;

public:
	Operand();
	Operand(T value, eOperandType type, std::string str)
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
		try
		{
			eOperandType max_type = std::max(this->getType(), rhs.getType());
			double result = std::stod(this->toString()) + std::stod(rhs.toString());

			std::ostringstream ss;
			ss << result;
			return Factory().createOperand(max_type, ss.str());
		}
		catch (std::exception &e)
		{
			throw Overflow();
		}
	}

	IOperand const * operator-( IOperand const & rhs ) const
	{
		eOperandType max_type = std::max(this->getType(), rhs.getType());
		double result = std::stod(this->toString()) - std::stod(rhs.toString());

		std::ostringstream ss;
		ss << result;
		return Factory().createOperand(max_type, ss.str());
		// return Factory().createOperand(max_type, std::to_string(result));
	}
	 // Difference
	IOperand const * operator*( IOperand const & rhs ) const
	{
		eOperandType max_type = std::max(this->getType(), rhs.getType());
		double result = std::stod(this->toString()) * std::stod(rhs.toString());

		std::ostringstream ss;
		ss << result;
		return Factory().createOperand(max_type, ss.str());
		// return Factory().createOperand(max_type, std::to_string(result));
	}
	 // Product
	IOperand const * operator/( IOperand const & rhs ) const
	{
		double znam = std::stod(rhs.toString());
		if (!znam)
			throw DivModByZero();
		eOperandType max_type = std::max(this->getType(), rhs.getType());
		double result = std::stod(this->toString()) / znam;

		std::ostringstream ss;
		ss << result;
		return Factory().createOperand(max_type, ss.str());
		// return Factory().createOperand(max_type, std::to_string(result));
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

		std::ostringstream ss;
		ss << result;
		return Factory().createOperand(max_type, ss.str());
		// return Factory().createOperand(max_type, std::to_string(result));
	}
	 // Modulo
	std::string const & toString(void) const // String representation of the instance
	{
		return value_str;
	}

};

#endif
