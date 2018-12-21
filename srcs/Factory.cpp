
#include "../includes/Factory.hpp"

IOperand const * Factory::createOperand(eOperandType type, std::string const & value ) const
{
	IOperand const * (Factory::*ptr[5])(std::string const & value) const;
	ptr[0] = &Factory::createInt8;
	ptr[1] = &Factory::createInt16;
	ptr[2] = &Factory::createInt32;
	ptr[3] = &Factory::createFloat;
	ptr[4] = &Factory::createDouble;

	return (this->*(ptr[type]))(value);
}

IOperand const *Factory::createInt8( std::string const & value)  const
{
	return new Operand<char>(value[0]);
}

IOperand const *Factory::createInt16( std::string const & value) const
{
	//???
	return new Operand<short>(std::stoi(value));
}

IOperand const *Factory::createInt32( std::string const & value) const
{
	return new Operand<int>(std::stoi(value));
}

IOperand const *Factory::createFloat( std::string const & value) const
{
	return new Operand<float>(std::stof(value));
}

IOperand const *Factory::createDouble( std::string const & value) const
{
	return new Operand<double>(std::stod(value));
}
