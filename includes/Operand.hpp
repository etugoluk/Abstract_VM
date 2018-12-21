#ifndef OPERAND_HPP
# define OPERAND_HPP

// #include "IOperand.hpp"
// #include "VM.hpp"

#include "Factory.hpp"

// enum eOperandType{Int8 = 0, Int16 = 1, Int32 = 2, Float = 3, Double = 4};

template <typename T>
class Operand : public IOperand
{
	T				value;
	std::string		value_str;
	eOperandType	type;

public:
	Operand();
	Operand(T value, eOperandType type) : value(value), type(type) {}
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
		return Factory().createOperand(type, this->toString() + rhs.toString());
	}
	 // Sum
	// IOperand const * operator-( IOperand const & rhs ) const
	// {
	// 	Operand *op = dynamic_cast<Operand*>(rhs); 
	// 	return new Operand<T>(this->value - op->value);
	// }
	//  // Difference
	// IOperand const * operator*( IOperand const & rhs ) const
	// {
	// 	Operand *op = dynamic_cast<Operand*>(rhs); 
	// 	return new Operand<T>(this->value * op->value);
	// }
	//  // Product
	// IOperand const * operator/( IOperand const & rhs ) const
	// {
	// 	Operand *op = dynamic_cast<Operand*>(rhs); 
	// 	return new Operand<T>(this->value / op->value);
	// }
	//  // Quotient
	// IOperand const * operator%( IOperand const & rhs ) const
	// {
	// 	Operand *op = dynamic_cast<Operand*>(rhs); 
	// 	return new Operand<T>(this->value % op->value);
	// }
	 // Modulo
	std::string const & toString(void) const // String representation of the instance
	{
		return value_str;
	}
};

#endif
