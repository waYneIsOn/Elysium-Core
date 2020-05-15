#include "BigInteger.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

const Elysium::Core::int32_t Elysium::Core::Math::Numerics::BigInteger::_CBITUINT = 32;

const Elysium::Core::Math::Numerics::BigInteger Elysium::Core::Math::Numerics::BigInteger::_MinusOneInt = Elysium::Core::Math::Numerics::BigInteger(-1);

Elysium::Core::Math::Numerics::BigInteger::BigInteger(const int32_t Sign, const Collections::Template::Array<uint32_t>& Value)
	: _Sign(Sign), _Bits(Collections::Template::Array<uint32_t>(Value))
{ }
Elysium::Core::Math::Numerics::BigInteger::BigInteger(const Collections::Template::Array<uint32_t>& Value, const bool IsNegative)
	: _Sign(0), _Bits(Collections::Template::Array<uint32_t>(Value))
{
	// ToDo!
}
Elysium::Core::Math::Numerics::BigInteger::BigInteger(const int32_t Value)
	: _Sign(Value == INT32_MIN_ ? -1 : (int32_t)Value), _Bits(Value == INT32_MIN_ ? Collections::Template::Array<uint32_t>(0) : Collections::Template::Array<uint32_t>(1))
{
	// ToDo!
	if (Value == INT32_MIN_)
	{
		_Bits[0] = static_cast<uint32_t>(Value);
	}
	else
	{

	}
}
Elysium::Core::Math::Numerics::BigInteger::BigInteger(const uint32_t Value)
	: _Sign(Value < INT32_MAX_ ? (int32_t)Value : 1), _Bits(Value < INT32_MAX_ ? Collections::Template::Array<uint32_t>(0) : Collections::Template::Array<uint32_t>(1))
{
	// ToDo!
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
Elysium::Core::Math::Numerics::BigInteger::BigInteger(BigInteger && Right) noexcept
	: _Sign(0), _Bits(Collections::Template::Array<uint32_t>(0))
{
	*this = std::move(Right);
}
Elysium::Core::Math::Numerics::BigInteger::~BigInteger()
{ }

Elysium::Core::Math::Numerics::BigInteger & Elysium::Core::Math::Numerics::BigInteger::operator=(const BigInteger & Source)
{
	if (this != &Source)
	{
		_Sign = Source._Sign;
		_Bits = Source._Bits;
	}
	return *this;
}
Elysium::Core::Math::Numerics::BigInteger & Elysium::Core::Math::Numerics::BigInteger::operator=(BigInteger && Right) noexcept
{
	if (this != &Right)
	{
		_Sign = std::move(Right._Sign);
		_Bits = std::move(Right._Bits);
	}
	return *this;
}

Elysium::Core::Math::Numerics::BigInteger Elysium::Core::Math::Numerics::BigInteger::operator<<(const int32_t & Shift)
{
	if (Shift == 0)
	{
		return *this;
	}
	else if (Shift == INT32_MIN_)
	{
		return ((*this >> INT32_MAX_) >> 1);
	}
	else if (Shift < 0)
	{
		return *this >> -Shift;
	}

	const int32_t DigitShift = Shift / _CBITUINT;
	const int32_t SmallShift = Shift - (DigitShift * _CBITUINT);

	Collections::Template::Array<uint32_t> Bits = Collections::Template::Array<uint32_t>(0);
	int32_t Length;
	const bool IsNegative = GetPartsForBitManipulation(*this, Bits, Length);

	int32_t zl = Length + DigitShift + 1;
	Collections::Template::Array<uint32_t> zd = Collections::Template::Array<uint32_t>(zl);

	if (SmallShift == 0)
	{
		for (int32_t i = 0; i < Length; i++)
		{
			zd[i + DigitShift] = Bits[i];
		}
	}
	else
	{
		int32_t CarryShift = _CBITUINT - SmallShift;
		uint32_t Carry = 0;
		int32_t i;
		for (i = 0; i < Length; i++)
		{
			uint32_t Rot = Bits[i];
			zd[i + DigitShift] = Rot << SmallShift | Carry;
			Carry = Rot >> CarryShift;
		}
		zd[i + DigitShift] = Carry;
	}

	return Elysium::Core::Math::Numerics::BigInteger(zd, IsNegative);
}
Elysium::Core::Math::Numerics::BigInteger Elysium::Core::Math::Numerics::BigInteger::operator>>(const int32_t & Shift)
{
	if (Shift == 0)
	{
		return *this;
	}
	else if (Shift == INT32_MIN_)
	{
		return ((*this << INT32_MAX_) << 1);
	}
	else if (Shift < 0)
	{
		return *this << -Shift;
	}

	const int32_t DigitShift = Shift / _CBITUINT;
	const int32_t SmallShift = Shift - (DigitShift * _CBITUINT);

	Collections::Template::Array<uint32_t> Bits = Collections::Template::Array<uint32_t>(0);
	int32_t Length;
	const bool IsNegative = GetPartsForBitManipulation(*this, Bits, Length);

	int32_t zl = Length + DigitShift + 1;
	Collections::Template::Array<uint32_t> zd = Collections::Template::Array<uint32_t>(zl);

	if (IsNegative)
	{
		if (Shift >= (_CBITUINT * Length))
		{
			return _MinusOneInt;
		}

		Collections::Template::Array<uint32_t> temp = Collections::Template::Array<uint32_t>(Length);
		Collections::Template::Array<uint32_t>::Copy(&Bits[0], &temp[0], Length);
		Bits = temp;
		// ToDo
	}
	// ToDo
	return Elysium::Core::Math::Numerics::BigInteger(1);
}

Elysium::Core::Math::Numerics::BigInteger Elysium::Core::Math::Numerics::BigInteger::operator|(const int32_t & Right)
{
	return Elysium::Core::Math::Numerics::BigInteger(1);
}

const bool Elysium::Core::Math::Numerics::BigInteger::GetPartsForBitManipulation(const BigInteger & Value, Collections::Template::Array<uint32_t>& Bits, int32_t& Length)
{
	if (Value._Bits.GetLength() == 0)
	{
		if (Value._Sign < 0)
		{
			Bits = Collections::Template::Array<uint32_t>(static_cast<uint32_t>(-Value._Sign));
		}
		else
		{
			Bits = Collections::Template::Array<uint32_t>(static_cast<uint32_t>(Value._Sign));
		}
	}
	else
	{
		Bits = Value._Bits;
	}
	Length = (Value._Bits.GetLength() == 0 ? 1 : Value._Bits.GetLength());

	return Value._Sign < 0;
}
