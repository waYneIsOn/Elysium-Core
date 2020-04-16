#include "BigInteger.hpp"

Elysium::Core::Math::Numerics::BigInteger::BigInteger(const uint32_t Value)
	: _Sign(Value < INT32_MAX_ ? (int32_t)Value : 1), _Bits(Value < INT32_MAX_ ? Collections::Template::Array<uint32_t>(0) : Collections::Template::Array<uint32_t>(1))
{
	if (Value >= INT32_MAX_)
	{
		_Bits[0] = Value;
	}
}
Elysium::Core::Math::Numerics::BigInteger::~BigInteger()
{ }
