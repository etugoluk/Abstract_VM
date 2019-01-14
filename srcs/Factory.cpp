
#include "../includes/Operand.hpp"

Factory::Factory() {}

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
	try
	{
		int res = std::stoi(value);

		if (res > std::numeric_limits<int8_t>::max())
			throw Overflow();
		if (res < std::numeric_limits<int8_t>::min())
			throw Overflow();
		return new Operand<int8_t>(static_cast<int8_t>(res), Int8, value);
	}
	catch (std::exception &e)
	{
		throw Overflow();
	}
}

IOperand const *Factory::createInt16( std::string const & value) const
{
	try
	{
		int res = std::stoi(value);

		if (res > std::numeric_limits<int16_t>::max())
			throw Overflow();
		if (res < std::numeric_limits<int16_t>::min())
			throw Overflow();
		return new Operand<int16_t>(static_cast<int16_t>(res), Int16, value);
	}
	catch (std::exception &e)
	{
		throw Overflow();
	}
}

IOperand const *Factory::createInt32( std::string const & value) const
{
	try
	{
		return new Operand<int>(std::stoi(value), Int32, value);
	}
	catch (std::exception &e)
	{
		throw Overflow();
	}
}

IOperand const *Factory::createFloat( std::string const & value) const
{
	try
	{
		return new Operand<float>(std::stof(value), Float, value);
	}
	catch (std::exception &e)
	{
		throw Overflow();
	}
}

IOperand const *Factory::createDouble( std::string const & value) const
{
	try
	{
		return new Operand<double>(std::stod(value), Double, value);
	}
	catch (std::exception &e)
	{
		throw Overflow();
	}
}
