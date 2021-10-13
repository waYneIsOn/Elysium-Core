#include "BigInteger.hpp"

#ifndef ELYSIUM_CORE_MATH_MATHHELPER
#include "MathHelper.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

const Elysium::Core::Math::Numerics::BigInteger Elysium::Core::Math::Numerics::BigInteger::_bnMinInt = Elysium::Core::Math::Numerics::BigInteger(-1, Elysium::Core::Collections::Template::Array<Elysium::Core::uint32_t>({ _uMaskHighBit }));
const Elysium::Core::Math::Numerics::BigInteger Elysium::Core::Math::Numerics::BigInteger::_MinusOneInt = Elysium::Core::Math::Numerics::BigInteger(-1);
const Elysium::Core::Math::Numerics::BigInteger Elysium::Core::Math::Numerics::BigInteger::_ZeroInt = Elysium::Core::Math::Numerics::BigInteger(0);

Elysium::Core::Math::Numerics::BigInteger::BigInteger(const Elysium::Core::int32_t Sign, const Collections::Template::Array<Elysium::Core::uint32_t>& Value)
	: _Sign(Sign), _Bits(Collections::Template::Array<uint32_t>(Value))
{ }
Elysium::Core::Math::Numerics::BigInteger::BigInteger(const Collections::Template::Array<Elysium::Core::uint32_t>& Value, const bool IsNegative)
	: _Sign(0), _Bits(Collections::Template::Array<Elysium::Core::uint32_t>(Value))
{
	Elysium::Core::int32_t Length;

	// Try to conserve space as much as possible by checking for wasted leading uint[] entries 
	// sometimes the uint[] has leading zeros from bit manipulation operations & and ^
	for (Length = Value.GetLength(); Length > 0 && Value[Length - 1] == 0; Length--);

	if (Length == 0)
	{
		*this = BigInteger(_ZeroInt);
	}
	else if (Length == 1 && Value[0] < _uMaskHighBit)
	{	// values like (Int32.MaxValue+1) are stored as "0x80000000" and as such cannot be packed into _sign
		_Sign = IsNegative ? -static_cast<int32_t>(Value[0]) : static_cast<int32_t>(Value[0]);
		_Bits = Collections::Template::Array<Elysium::Core::uint32_t>(0);

		// Although Int32.MinValue fits in _sign, we represent this case differently for negate
		if (_Sign == Elysium::Core::UInt32::GetMinValue())
		{
			*this = BigInteger(_bnMinInt);
		}
	}
	else
	{
		_Sign = IsNegative ? -1 : +1;
		_Bits = Collections::Template::Array<Elysium::Core::uint32_t>(Length);
		Collections::Template::Array<Elysium::Core::uint32_t>::Copy(&Value[0], &_Bits[0], Length);
	}
}
Elysium::Core::Math::Numerics::BigInteger::BigInteger(Collections::Template::Array<Elysium::Core::uint32_t>& Value)
	: _Sign(0), _Bits(Value)
{ 
	int32_t DWordCount = Value.GetLength();
	const bool IsNegative = DWordCount > 0 && ((Value[DWordCount - 1] & 0x80000000) == 0x80000000);

	while (DWordCount > 0 && Value[DWordCount - 1] == 0)
	{
		DWordCount--;
	}

	if (DWordCount == 0)
	{
		*this = _ZeroInt;
	}
	else if (DWordCount == 1)
	{
		if (static_cast<Elysium::Core::int32_t>(Value[0]) < 0 && !IsNegative)
		{
			_Bits = Collections::Template::Array<uint32_t>(1);
			_Bits[0] = Value[0];
			_Sign = +1;
		}
		else if (static_cast<Elysium::Core::int32_t>(Value[0]) == Elysium::Core::Int32::GetMinValue())
		{
			*this = _bnMinInt;
		}
		else
		{
			_Sign = static_cast<Elysium::Core::int32_t>(Value[0]);
			_Bits = Collections::Template::Array<Elysium::Core::uint32_t>(0);
		}
	}
	else
	{
		if (!IsNegative)
		{
			if (DWordCount != Value.GetLength())
			{
				_Sign = +1;
				_Bits = Collections::Template::Array<Elysium::Core::uint32_t>(DWordCount);
				Collections::Template::Array<Elysium::Core::uint32_t>::Copy(&Value[0], &_Bits[0], DWordCount);
			}
			else
			{
				_Sign = +1;
				_Bits = Value;
			}
		}
		else
		{
			// finally handle the more complex cases where we must transform the input into sign magnitude
			DangerousMakeTwosComplement(Value);	// mutates Value

			// pack _bits to remove any wasted space after the twos complement
			Elysium::Core::size Length = Value.GetLength();
			while (Length > 0 && Value[Length - 1] == 0) 
			{
				Length--;
			}

			if (Length == 1 && static_cast<Elysium::Core::int32_t>(Value[0]) > 0)
			{	// the number is represented by a single dword
				if (Value[0] == 1)
				{
					*this = _MinusOneInt;
				}
				else if (Value[0] == _uMaskHighBit)
				{
					*this = _bnMinInt;
				}
				else
				{
					_Sign = -1 * static_cast<Elysium::Core::int32_t>(Value[0]);
					_Bits = Collections::Template::Array<Elysium::Core::uint32_t>(0);
				}
			}
			else if (Length != Value.GetLength())
			{	// the number is represented by multiple dwords
				// trim off any wasted uint values when possible
				_Sign = -1;
				_Bits = Collections::Template::Array<Elysium::Core::uint32_t>(Length);
				Collections::Template::Array<Elysium::Core::uint32_t>::Copy(&Value[0], &_Bits[0], Length);
			}
			else
			{	// no trimming is possible. Assign value directly to _Bits.  
				_Sign = -1;
				_Bits = Value;
			}
		}
	}
}
Elysium::Core::Math::Numerics::BigInteger::BigInteger(const Elysium::Core::int32_t Value)
	: _Sign(Value == Elysium::Core::Int32::GetMinValue() ? -1 : (Elysium::Core::int32_t)Value),
	_Bits(Value == Elysium::Core::Int32::GetMinValue() ? Collections::Template::Array<Elysium::Core::uint32_t>(0) : Collections::Template::Array<Elysium::Core::uint32_t>(1))
{
	if (Value == Elysium::Core::Int32::GetMinValue())
	{
		*this = BigInteger(_bnMinInt);
	}
	else
	{
		_Sign = Value;
		_Bits = Collections::Template::Array<Elysium::Core::uint32_t>(0);
	}
}
Elysium::Core::Math::Numerics::BigInteger::BigInteger(const Elysium::Core::uint32_t Value)
	: _Sign(Value < Elysium::Core::Int32::GetMaxValue() ? (Elysium::Core::int32_t)Value : 1),
	_Bits(Value < Elysium::Core::Int32::GetMaxValue() ? Collections::Template::Array<Elysium::Core::uint32_t>(0) : Collections::Template::Array<Elysium::Core::uint32_t>(1))
{
	if (Value <= Elysium::Core::Int32::GetMaxValue())
	{
		_Sign = static_cast<int32_t>(Value);
		_Bits = Collections::Template::Array<Elysium::Core::uint32_t>(0);
	}
	else
	{
		_Sign = 1;
		_Bits = Collections::Template::Array<Elysium::Core::uint32_t>(1);
		_Bits[0] = Value;
	}
}
Elysium::Core::Math::Numerics::BigInteger::BigInteger(const Collections::Template::Array<byte>& Value)
	: _Sign(0), _Bits(Collections::Template::Array<Elysium::Core::uint32_t>(Value.GetLength() / 4))
{ 
	Elysium::Core::int32_t ByteCount = Value.GetLength();
	bool IsNegative = ByteCount > 0 && ((Value[ByteCount - 1] & 0x80) == 0x80);

	// Try to conserve space as much as possible by checking for wasted leading byte[] entries 
	while (ByteCount > 0 && Value[ByteCount - 1] == 0)
	{
		ByteCount--;
	}

	if (ByteCount == 0)
	{
		_Sign = 0;
		_Bits = Collections::Template::Array<Elysium::Core::uint32_t>(0);
	}
	else if (ByteCount <= 4)
	{
		if (IsNegative)
		{
			_Sign = static_cast<Elysium::Core::int32_t>(0xffffffff);
		}
		else
		{
			_Sign = 0;
		}

		for (Elysium::Core::int32_t i = ByteCount - 1; i >= 0; i--)
		{
			_Sign <<= 8;
			_Sign |= Value[i];
		}
		_Bits = Collections::Template::Array<Elysium::Core::uint32_t>(0);

		if (_Sign < 0 && !IsNegative)
		{
			// int32 overflow
			// example: Int64 value 2362232011 (0xCB, 0xCC, 0xCC, 0x8C, 0x0)
			// can be naively packed into 4 bytes (due to the leading 0x0)
			// it overflows into the int32 sign bit
			_Bits = Collections::Template::Array<Elysium::Core::uint32_t>(1);
			_Bits[0] = static_cast<Elysium::Core::uint32_t>(_Sign);
			_Sign = +1;
		}

		if (_Sign == Elysium::Core::Int32::GetMinValue())
		{
			*this = _bnMinInt;
		}
	}
	else
	{
		Elysium::Core::int32_t UnalignedBytes = ByteCount % 4;
		Elysium::Core::int32_t DWordCount = ByteCount & 4 + (UnalignedBytes == 0 ? 0 : 1);
		bool IsZero = true;
		Collections::Template::Array<Elysium::Core::uint32_t> Val = Collections::Template::Array<Elysium::Core::uint32_t>(1);

		// Copy all dwords, except but don't do the last one if it's not a full four bytes
		Elysium::Core::int32_t CurrentDWord;
		Elysium::Core::int32_t CurrentByte;
		Elysium::Core::int32_t ByteInDWord;
		CurrentByte = 3;
		for (CurrentDWord = 0; CurrentDWord < DWordCount - (UnalignedBytes == 0 ? 0 : 1); CurrentDWord++)
		{
			ByteInDWord = 0;
			while (ByteInDWord < 4)
			{
				if (Value[CurrentByte] != 0x00)
				{
					IsZero = false;
				}
				Val[CurrentDWord] <<= 8;
				Val[CurrentDWord] |= Value[CurrentByte];
				CurrentByte--;
				ByteInDWord++;
			}
			CurrentByte += 8;
		}

		// Copy the last dword specially if it's not aligned
		if (UnalignedBytes != 0)
		{
			if (IsNegative)
			{
				Val[DWordCount - 1] = 0xffffffff;
				for (CurrentByte = ByteCount - 1; CurrentByte >= ByteCount - UnalignedBytes; CurrentByte--)
				{
					if (Value[CurrentByte] != 0x00)
					{
						IsZero = false;
					}
					Val[CurrentDWord] <<= 8;
					Val[CurrentDWord] |= Value[CurrentByte];
				}
			}
		}

		if (IsZero)
		{
			*this = BigInteger(_ZeroInt);
		}
		else if (IsNegative)
		{
			DangerousMakeTwosComplement(Val);	// mutates Val

			// pack _bits to remove any wasted space after the twos complement
			Elysium::Core::int32_t Length = Val.GetLength();
			while (Length > 0 && Val[Length - 1] == 0)
			{
				Length--;
			}

			if (Length == 1 && static_cast<int32_t>(Val[0]) > 0)
			{
				if (Val[0] == 1)
				{
					*this = BigInteger(_MinusOneInt);
				}
				else if (Val[0] == _uMaskHighBit)
				{
					*this = BigInteger(_bnMinInt);
				}
				else
				{
					_Sign = (-1) * static_cast<Elysium::Core::int32_t>(Val[0]);
					_Bits = Collections::Template::Array<Elysium::Core::uint32_t>(0);
				}
			}
			else if (Length != Val.GetLength())
			{
				_Sign = -1;
				_Bits = Collections::Template::Array<Elysium::Core::uint32_t>(Length);
				Collections::Template::Array<Elysium::Core::uint32_t>::Copy(&Val[0], &_Bits[0], Length);
			}
			else
			{
				_Sign = -1;
				_Bits = Val;
			}
		}
		else
		{
			_Sign = +1;
			_Bits = Val;
		}
	}
}
Elysium::Core::Math::Numerics::BigInteger::BigInteger(const BigInteger & Source)
	: _Sign(Source._Sign), _Bits(Source._Bits)
{ }
Elysium::Core::Math::Numerics::BigInteger::BigInteger(BigInteger && Right) noexcept
	: _Sign(0), _Bits(Collections::Template::Array<Elysium::Core::uint32_t>(0))
{
	*this = Elysium::Core::Template::Functional::Move(Right);
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
		_Sign = Elysium::Core::Template::Functional::Move(Right._Sign);
		_Bits = Elysium::Core::Template::Functional::Move(Right._Bits);
	}
	return *this;
}

Elysium::Core::Math::Numerics::BigInteger Elysium::Core::Math::Numerics::BigInteger::operator<<(const Elysium::Core::int32_t & Shift)
{
	if (Shift == 0)
	{
		return *this;
	}
	else if (Shift == Elysium::Core::Int32::GetMinValue())
	{
		return ((*this >> Elysium::Core::Int32::GetMaxValue()) >> 1);
	}
	else if (Shift < 0)
	{
		return *this >> -Shift;
	}

	const Elysium::Core::int32_t DigitShift = Shift / _CBITUINT;
	const Elysium::Core::int32_t SmallShift = Shift - (DigitShift * _CBITUINT);

	Collections::Template::Array<Elysium::Core::uint32_t> Bits = Collections::Template::Array<Elysium::Core::uint32_t>(0);
	Elysium::Core::int32_t Length;
	const bool IsNegative = GetPartsForBitManipulation(*this, Bits, Length);

	Elysium::Core::int32_t zl = Length + DigitShift + 1;
	Collections::Template::Array<Elysium::Core::uint32_t> zd = Collections::Template::Array<Elysium::Core::uint32_t>(zl);

	if (SmallShift == 0)
	{
		for (Elysium::Core::int32_t i = 0; i < Length; i++)
		{
			zd[i + DigitShift] = Bits[i];
		}
	}
	else
	{
		Elysium::Core::int32_t CarryShift = _CBITUINT - SmallShift;
		Elysium::Core::uint32_t Carry = 0;
		Elysium::Core::int32_t i;
		for (i = 0; i < Length; i++)
		{
			Elysium::Core::uint32_t Rot = Bits[i];
			zd[i + DigitShift] = Rot << SmallShift | Carry;
			Carry = Rot >> CarryShift;
		}
		zd[i + DigitShift] = Carry;
	}

	return Elysium::Core::Math::Numerics::BigInteger(zd, IsNegative);
}
Elysium::Core::Math::Numerics::BigInteger Elysium::Core::Math::Numerics::BigInteger::operator>>(const Elysium::Core::int32_t & Shift)
{
	if (Shift == 0)
	{
		return *this;
	}
	else if (Shift == Elysium::Core::Int32::GetMinValue())
	{
		return ((*this << Elysium::Core::Int32::GetMaxValue()) << 1);
	}
	else if (Shift < 0)
	{
		return *this << -Shift;
	}

	const Elysium::Core::int32_t DigitShift = Shift / _CBITUINT;
	const Elysium::Core::int32_t SmallShift = Shift - (DigitShift * _CBITUINT);

	Collections::Template::Array<Elysium::Core::uint32_t> Bits = Collections::Template::Array<Elysium::Core::uint32_t>(0);
	Elysium::Core::int32_t Length;
	const bool IsNegative = GetPartsForBitManipulation(*this, Bits, Length);

	if (IsNegative)
	{
		if (Shift >= (_CBITUINT * Length))
		{
			return _MinusOneInt;
		}

		Collections::Template::Array<Elysium::Core::uint32_t> Temp = Collections::Template::Array<Elysium::Core::uint32_t>(Length);
		Collections::Template::Array<Elysium::Core::uint32_t>::Copy(&Bits[0], &Temp[0], Length);
		Bits = Temp;
		DangerousMakeTwosComplement(Bits);
	}

	Elysium::Core::int32_t zl = Length - DigitShift;
	if (zl < 0)
	{
		zl = 0;
	}
	Collections::Template::Array<Elysium::Core::uint32_t> zd = Collections::Template::Array<Elysium::Core::uint32_t>(zl);

	if (SmallShift == 0)
	{
		for (Elysium::Core::int32_t i = Length - 1; i >= DigitShift; i--)
		{
			zd[i - DigitShift] = Bits[i];
		}
	}
	else
	{
		Elysium::Core::int32_t CarryShift = _CBITUINT - SmallShift;
		Elysium::Core::uint32_t Carry = 0;
		for (int32_t i = Length - 1; i >= DigitShift; i--)
		{
			Elysium::Core::uint32_t rot = Bits[i];
			if (IsNegative && i == Length - 1)
			{	// sign-extend the first shift for negative ints then let the carry propagate
				zd[i - DigitShift] = (rot >> SmallShift) | (0xFFFFFFFF << CarryShift);
			}
			else
			{
				zd[i - DigitShift] = (rot >> SmallShift) | Carry;
			}
			Carry = rot << CarryShift;
		}
	}

	if (IsNegative)
	{
		DangerousMakeTwosComplement(zd);	// mutates zd
	}

	return Elysium::Core::Math::Numerics::BigInteger(zd, IsNegative);
}

Elysium::Core::Math::Numerics::BigInteger Elysium::Core::Math::Numerics::BigInteger::operator|(const BigInteger & Right)
{
	if (GetIsZero())
	{
		return Right;
	}
	if (Right.GetIsZero() == 0)
	{
		return *this;
	}

	Collections::Template::Array<Elysium::Core::uint32_t> x = ToUInt32Array();
	Collections::Template::Array<Elysium::Core::uint32_t> y = Right.ToUInt32Array();
	Collections::Template::Array<Elysium::Core::uint32_t> z = Collections::Template::Array<Elysium::Core::uint32_t>(MathHelper::Max(x.GetLength(), y.GetLength()));
	Elysium::Core::uint32_t xExtend = _Sign < 0 ? Elysium::Core::UInt32::GetMaxValue() : 0;
	Elysium::Core::uint32_t yExtend = Right._Sign < 0 ? Elysium::Core::UInt32::GetMaxValue() : 0;

	for (Elysium::Core::size i = 0; i < z.GetLength(); i++)
	{
		Elysium::Core::uint32_t xu = i < x.GetLength() ? x[i] : xExtend;
		Elysium::Core::uint32_t yu = i < y.GetLength() ? y[i] : yExtend;
		z[i] = xu | yu;
	}
	
	return Elysium::Core::Math::Numerics::BigInteger(z);
}

const bool Elysium::Core::Math::Numerics::BigInteger::GetIsZero() const
{
	return _Sign == 0;
}

const Elysium::Core::int32_t Elysium::Core::Math::Numerics::BigInteger::GetSign() const
{
	return (_Sign >> (_CBitUint32 -1)) - (-_Sign >> (_CBitUint32 -1));
}

const bool Elysium::Core::Math::Numerics::BigInteger::GetPartsForBitManipulation(const BigInteger & Value, Collections::Template::Array<Elysium::Core::uint32_t>& Bits, Elysium::Core::int32_t& Length)
{
	if (Value._Bits.GetLength() == 0)
	{
		if (Value._Sign < 0)
		{
			Bits = Collections::Template::Array<uint32_t>({ static_cast<uint32_t>(-Value._Sign) });
		}
		else
		{
			Bits = Collections::Template::Array<uint32_t>({ static_cast<uint32_t>(Value._Sign) });
		}
	}
	else
	{
		Bits = Value._Bits;
	}
	Length = (Value._Bits.GetLength() == 0 ? 1 : Value._Bits.GetLength());

	return Value._Sign < 0;
}

const Elysium::Core::Collections::Template::Array<Elysium::Core::uint32_t> Elysium::Core::Math::Numerics::BigInteger::ToUInt32Array() const
{
	if (_Bits.GetLength() == 0 && _Sign == 0)
	{
		return Elysium::Core::Collections::Template::Array<uint32_t>({ 0 });
	}

	Elysium::Core::Collections::Template::Array<Elysium::Core::uint32_t> DWords = Elysium::Core::Collections::Template::Array<Elysium::Core::uint32_t>(0);
	uint32_t HighDWord;

	if (_Bits.GetLength() == 0)
	{
		DWords = Elysium::Core::Collections::Template::Array<Elysium::Core::uint32_t>({ static_cast<Elysium::Core::uint32_t>(_Sign) });
		HighDWord = _Sign < 0 ? Elysium::Core::UInt32::GetMaxValue() : 0;
	}
	else if (_Sign == -1)
	{
		DWords = _Bits;
		HighDWord = Elysium::Core::UInt32::GetMaxValue();
	}
	else
	{
		DWords = _Bits;
		HighDWord = 0;
	}

	// find highest significatn byte
	int32_t msb;
	for (msb = DWords.GetLength() - 1; msb > 0; msb--)
	{
		if (DWords[msb] != HighDWord)
		{
			break;
		}
	}

	// ensure high bit is 0 if positive, 1 if negative
	bool NeedExtraByte = (DWords[msb] & 0x80000000) != (HighDWord & 0x80000000);

	Elysium::Core::Collections::Template::Array<Elysium::Core::uint32_t> Trimmed = Elysium::Core::Collections::Template::Array<Elysium::Core::uint32_t>(msb + 1 + (NeedExtraByte ? 1 : 0));
	Elysium::Core::Collections::Template::Array<Elysium::Core::uint32_t>::Copy(&DWords[0], &Trimmed[0], msb + 1);

	if (NeedExtraByte)
	{
		Trimmed[Trimmed.GetLength() - 1] = HighDWord;
	}

	return Trimmed;
}

const Elysium::Core::Collections::Template::Array<Elysium::Core::uint32_t> Elysium::Core::Math::Numerics::BigInteger::DangerousMakeTwosComplement(Elysium::Core::Collections::Template::Array<Elysium::Core::uint32_t> & d)
{	// first do complement and +1 as long as carry is needed
	Elysium::Core::int32_t i = 0;
	Elysium::Core::uint32_t v = 0;
	for (; i < d.GetLength(); i++)
	{
		v = ~d[i] + 1;
		d[i] = v;
		if (v != 0)
		{
			i++;
			break;
		}
	}

	if (v != 0)
	{	// now ones complement is sufficient
		for (; i < d.GetLength(); i++)
		{
			d[i] = ~d[i];
		}
	}
	else
	{	//??? this is weird
		d = Resize(d, d.GetLength() + 1);
		d[d.GetLength() - 1] = 1;
	}
	return d;
}

const Elysium::Core::Collections::Template::Array<Elysium::Core::uint32_t> Elysium::Core::Math::Numerics::BigInteger::Resize(Elysium::Core::Collections::Template::Array<uint32_t>& Value, const Elysium::Core::int32_t Length)
{
	if (Value.GetLength() == Length)
	{
		return Value;
	}

	Collections::Template::Array<Elysium::Core::uint32_t> Result = Collections::Template::Array<Elysium::Core::uint32_t>(Length);
	Elysium::Core::int32_t NewLength = Elysium::Core::Math::MathHelper::Min(Value.GetLength(), Length);
	for (Elysium::Core::int32_t i = 0; i < NewLength; i++)
	{
		Result[i] = Value[i];
	}
	return Result;
}
