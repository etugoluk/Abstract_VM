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
	Operand(Operand const &o)
	: value(o.value), value_str(o.str), type(o.type) {}
	Operand & operator=(Operand const &o)
	{
		if (this != &o)
		{
			value = o.value;
			value_str = o.str;
			type = o.type;
		}
		return *this;
	}
	~Operand() {}

	int getPrecision( void ) const
	{
		return type;
	}

	eOperandType getType( void ) const
	{
		return type;
	}

	IOperand const * operator+( IOperand const & rhs ) const
	{
		std::ostringstream ss;
		try
		{
			eOperandType max_type = std::max(this->getType(), rhs.getType());
			double result = std::stod(this->toString()) + std::stod(rhs.toString());
			ss << result;
			return Factory().createOperand(max_type, ss.str());
		}
		catch (std::exception &e)
		{
			throw Overflow(ss.str());
		}
	}

	IOperand const * operator-( IOperand const & rhs ) const
	{
		std::ostringstream ss;
		try
		{
			eOperandType max_type = std::max(this->getType(), rhs.getType());
			double result = std::stod(this->toString()) - std::stod(rhs.toString());
			ss << result;
			return Factory().createOperand(max_type, ss.str());
		}
		catch (std::exception &e)
		{
			throw Overflow(ss.str());
		}
	}

	IOperand const * operator*( IOperand const & rhs ) const
	{
		std::ostringstream ss;
		try
		{
			eOperandType max_type = std::max(this->getType(), rhs.getType());
			double result = std::stod(this->toString()) * std::stod(rhs.toString());
			ss << result;
			return Factory().createOperand(max_type, ss.str());
		}
		catch (std::exception &e)
		{
			throw Overflow(ss.str());
		}
	}

	IOperand const * operator/( IOperand const & rhs ) const
	{
		std::ostringstream ss;
		try
		{
			double znam = std::stod(rhs.toString());
			if (!znam)
				throw DivModByZero();
			eOperandType max_type = std::max(this->getType(), rhs.getType());
			double result = std::stod(this->toString()) / znam;
			ss << result;
			return Factory().createOperand(max_type, ss.str());
		}
		catch (DivModByZero &d)
		{
			throw DivModByZero();
		}
		catch (std::exception &e)
		{
			throw Overflow(ss.str());
		}
	}

	IOperand const * operator%( IOperand const & rhs ) const
	{
		std::ostringstream ss;
		try
		{
			eOperandType max_type = std::max(this->getType(), rhs.getType());
			if (max_type > 2)
				throw std::invalid_argument("bad type");
			int znam = std::stoi(rhs.toString());
			if (!znam)
				throw DivModByZero();
			int result = std::stoi(this->toString()) % std::stoi(rhs.toString());
			ss << result;
			return Factory().createOperand(max_type, ss.str());
		}
		catch (DivModByZero &d)
		{
			throw DivModByZero();
		}
		catch (std::exception &e)
		{
			throw Overflow(ss.str());
		}
	}

	bool operator>( IOperand const & rhs ) const
	{
		double rv = std::stod(rhs.toString());
		double lv = std::stod(this->toString());

		return (lv > rv) ? true : false;
	}

	bool operator<( IOperand const & rhs ) const
	{
		double rv = std::stod(rhs.toString());
		double lv = std::stod(this->toString());

		return (lv < rv) ? true : false;
	}

	bool operator>=( IOperand const & rhs ) const
	{
		return !(*this < rhs);
	}

	bool operator<=( IOperand const & rhs ) const
	{
		return !(*this > rhs);
	}

	bool operator==( IOperand const & rhs ) const
	{
		double rv = std::stod(rhs.toString());
		double lv = std::stod(this->toString());

		return (lv == rv) ? true : false;
	}

	bool operator!=( IOperand const & rhs ) const
	{
		return !(*this == rhs);
	}

	std::string const & toString(void) const
	{
		return value_str;
	}

};

#endif
