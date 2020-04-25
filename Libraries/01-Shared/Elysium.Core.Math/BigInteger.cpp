#include "BigInteger.hpp"

Elysium::Core::Math::Numerics::BigInteger::BigInteger(const uint32_t Value)
	: _Sign(Value < INT32_MAX_ ? (int32_t)Value : 1), _Bits(Value < INT32_MAX_ ? Collections::Template::Array<uint32_t>(0) : Collections::Template::Array<uint32_t>(1))
{
	if (Value >= INT32_MAX_)
	{
		_Bits[0] = Value;
	}
}
Elysium::Core::Math::Numerics::BigInteger::BigInteger(const Collections::Template::Array<byte>& Value)
	: _Sign(0), _Bits(Collections::Template::Array<uint32_t>(Value.GetLength() / 4))
{ 
	// ToDo!
}
Elysium::Core::Math::Numerics::BigInteger::BigInteger(const BigInteger & Source)
	: _Sign(Source._Sign), _Bits(Source._Bits)
{ }
Elysium::Core::Math::Numerics::BigInteger::~BigInteger()
{ }
