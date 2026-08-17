/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

Code translated and edited from original implementation:
https://referencesource.microsoft.com/#System.Numerics/System/Numerics/BigInteger.cs
Copyright (c) Microsoft Corporation. All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_MATH_NUMERICS_BIGINTEGER
#define ELYSIUM_CORE_TEMPLATE_MATH_NUMERICS_BIGINTEGER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_SIGNEDINTEGER
#include "../../Concepts/SignedInteger.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_UNSIGNEDINTEGER
#include "../../Concepts/UnsignedInteger.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../../Container/Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../../Functional/Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_REMOVECONSTVOLATILE
#include "../../Functional/RemoveConstVolatile.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_MAX
#include "../Max.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_MIN
#include "../Min.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NUMERIC_NUMERICTRAITS
#include "../../Numeric/NumericTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_ARCHTECTURE
#include "../../System/Architecture.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "../../Text/String.hpp"
#endif

namespace Elysium::Core::Template::Math::Numerics
{
	template <Elysium::Core::Template::Concepts::SignedInteger Sign = Elysium::Core::Template::System::int32_t,
		Elysium::Core::Template::Concepts::UnsignedInteger Limb = Elysium::Core::Template::Numeric::NumericTraits<Sign>::UnsignedType>
	class BigInteger
	{
	public:
		using SignType = Elysium::Core::Template::Functional::RemoveConstVolatileType<Sign>;

		using LimbType = Elysium::Core::Template::Functional::RemoveConstVolatileType<Limb>;
	private:
		inline static constexpr const Elysium::Core::Template::System::uint8_t SignTypeBitWidth = sizeof(SignType) * Elysium::Core::Template::System::Architecture::BitsPerByte;

		inline static constexpr const SignType MaskHighBit = Elysium::Core::Template::Numeric::NumericTraits<LimbType>::Minimum;
	public:
		constexpr BigInteger() = delete;

		inline constexpr BigInteger(const SignType Value) noexcept
			: _SignOrValue(Value), _Limbs{}
		{ }
		/*
		inline constexpr BigInteger(const LimbType Value)
			: _SignOrValue(Value <= Elysium::Core::Template::Numeric::NumericTraits<SignType>::Maximum ? Value : 0), _Limbs{}
		{ }
		*/
		inline constexpr BigInteger(const SignType SignOrValue, const Elysium::Core::Template::Container::Vector<LimbType>& Limbs)
			: _SignOrValue(SignOrValue), _Limbs(Limbs)
		{ }
		
		inline constexpr BigInteger(const Elysium::Core::Template::Container::Vector<LimbType>& Value, const bool IsNegative)
			: _SignOrValue(0), _Limbs(Value)
		{
			Elysium::Core::Template::System::size Length;

			// Try to conserve space as much as possible by checking for wasted leading uint[] entries 
			// sometimes the uint[] has leading zeros from bit manipulation operations & and ^
			for (Length = Value.GetLength(); Length > 0 && Value[Length - 1] == 0; --Length);

			if (Length == 0)
			{
				*this = Zero();
			}
			else if (Length == 1 && Value[0] < MaskHighBit)
			{	// values like (Int32.MaxValue+1) are stored as "0x80000000" and as such cannot be packed into _sign
				_SignOrValue = IsNegative ? -static_cast<SignType>(Value[0]) : static_cast<SignType>(Value[0]);
				_Limbs.Resize(0);

				// Although Int32.MinValue fits in _sign, we represent this case differently for negate
				if (_SignOrValue == Elysium::Core::Template::Numeric::NumericTraits<Limb>::Minimum)
				{
					*this = MinusOne();
				}
			}
			else
			{
				_SignOrValue = IsNegative ? -1 : +1;
				_Limbs.Resize(Length);
				Elysium::Core::Template::Memory::MemCpy(&_Limbs[0], &Value[0], Value.GetLength());
			}
		}

		inline constexpr BigInteger(Elysium::Core::Template::Container::Vector<LimbType>& Value)
			: _SignOrValue(0), _Limbs(Value)
		{
			Elysium::Core::Template::System::size DWordCount = Value.GetLength();
			const bool IsNegative = DWordCount > 0 && ((Value[DWordCount - 1] & 0x80000000) == 0x80000000);

			while (DWordCount > 0 && Value[DWordCount - 1] == 0)
			{
				--DWordCount;
			}

			if (DWordCount == 0)
			{
				*this = Zero();
			}
			else if (DWordCount == 1)
			{
				if (static_cast<SignType>(Value[0]) < 0 && !IsNegative)
				{
					_Limbs.Resize(1);
					_Limbs[0] = Value[0];
					_SignOrValue = +1;
				}
				else if (static_cast<SignType>(Value[0]) == Elysium::Core::Template::Numeric::NumericTraits<Limb>::Minimum)
				{
					*this = Min();
				}
				else
				{
					_SignOrValue = static_cast<SignType>(Value[0]);
					_Limbs.Resize(0);
				}
			}
			else
			{
				if (!IsNegative)
				{
					if (DWordCount != Value.GetLength())
					{
						_SignOrValue = +1;
						_Limbs.Resize(DWordCount);
						Elysium::Core::Template::Memory::MemCpy(&_Limbs[0], &Value[0], Value.GetLength());
					}
					else
					{
						_SignOrValue = +1;
						_Limbs = Value;
					}
				}
				else
				{
					// finally handle the more complex cases where we must transform the input into sign magnitude
					DangerousMakeTwosComplement(Value);	// mutates Value

					// pack _bits to remove any wasted space after the twos complement
					Elysium::Core::Template::System::size Length = Value.GetLength();
					while (Length > 0 && Value[Length - 1] == 0)
					{
						Length--;
					}

					if (Length == 1 && static_cast<SignType>(Value[0]) > 0)
					{	// the number is represented by a single dword
						if (Value[0] == 1)
						{
							*this = MinusOne();
						}
						else if (Value[0] == MaskHighBit)
						{
							*this = Min();
						}
						else
						{
							_SignOrValue = -1 * static_cast<SignType>(Value[0]);
							_Limbs.Resize(0);
						}
					}
					else if (Length != Value.GetLength())
					{	// the number is represented by multiple dwords
						// trim off any wasted uint values when possible
						_SignOrValue = -1;
						_Limbs.Resize(Length);
						Elysium::Core::Template::Memory::MemCpy(&_Limbs[0], &Value[0], Value.GetLength());
					}
					else
					{	// no trimming is possible. Assign value directly to _Bits.  
						_SignOrValue = -1;
						_Limbs = Value;
					}
				}
			}
		}
		
		inline constexpr BigInteger(const BigInteger& Source)
			: _SignOrValue(Source._SignOrValue), _Limbs(Source._Limbs)
		{ }

		inline constexpr BigInteger(BigInteger&& Right) noexcept
		{
			*this = Elysium::Core::Template::Functional::Move(Right);
		}

		constexpr ~BigInteger() = default;
	public:
		inline constexpr BigInteger& operator=(const BigInteger& Source)
		{
			if (this != &Source)
			{
				_SignOrValue = Source._SignOrValue;
				_Limbs = Source._Limbs;
			}
			return *this;
		}

		inline constexpr BigInteger& operator=(BigInteger&& Right) noexcept
		{
			if (this != &Right)
			{
				_SignOrValue = Elysium::Core::Template::Functional::Move(Right._SignOrValue);
				_Limbs = Elysium::Core::Template::Functional::Move(Right._Limbs);
			}
			return *this;
		}
	public:
		inline constexpr BigInteger operator<<(const SignType Shift)
		{
			if (Shift == 0)
			{
				return *this;
			}
			else if (Shift == Elysium::Core::Template::Numeric::NumericTraits<SignType>::Minimum)
			{
				return ((*this >> Elysium::Core::Template::Numeric::NumericTraits<SignType>::Maximum) >> 1);
			}
			else if (Shift < 0)
			{
				return *this >> -Shift;
			}

			const LimbType DigitShift = Shift / SignTypeBitWidth;
			const LimbType SmallShift = Shift - (DigitShift * SignTypeBitWidth);

			Elysium::Core::Template::Container::Vector<LimbType> Bits(0);
			SignType Length;
			const bool IsNegative = GetPartsForBitManipulation(*this, Bits, Length);

			Elysium::Core::Template::System::size zl = Length + DigitShift + 1;
			Elysium::Core::Template::Container::Vector<LimbType> zd(zl);

			if (SmallShift == 0)
			{
				for (Elysium::Core::Template::System::int32_t i = 0; i < Length; ++i)
				{
					zd[i + DigitShift] = Bits[i];
				}
			}
			else
			{
				Elysium::Core::Template::System::int32_t CarryShift = SignTypeBitWidth - SmallShift;
				Elysium::Core::Template::System::uint32_t Carry = 0;
				Elysium::Core::Template::System::int32_t i;
				for (i = 0; i < Length; ++i)
				{
					Elysium::Core::Template::System::uint32_t Rot = Bits[i];
					zd[i + DigitShift] = Rot << SmallShift | Carry;
					Carry = Rot >> CarryShift;
				}
				zd[i + DigitShift] = Carry;
			}

			return BigInteger(zd, IsNegative);
		}

		inline constexpr BigInteger operator>>(const SignType Shift)
		{
			if (Shift == 0)
			{
				return *this;
			}
			else if (Shift == Elysium::Core::Template::Numeric::NumericTraits<SignType>::Minimum)
			{
				return ((*this << Elysium::Core::Template::Numeric::NumericTraits<SignType>::Maximum) << 1);
			}
			else if (Shift < 0)
			{
				return *this << -Shift;
			}

			const SignType DigitShift = Shift / SignTypeBitWidth;
			const SignType SmallShift = Shift - (DigitShift * SignTypeBitWidth);

			Elysium::Core::Template::Container::Vector<LimbType> Bits(0);
			SignType Length;
			const bool IsNegative = GetPartsForBitManipulation(*this, Bits, Length);

			if (IsNegative)
			{
				if (Shift >= (SignTypeBitWidth * Length))
				{
					return MinusOne();
				}

				Elysium::Core::Template::Container::Vector<LimbType> Temp(Length);
				Elysium::Core::Template::Memory::MemCpy(&Temp[0], &Bits[0], Bits.GetLength());
				Bits = Temp;
				DangerousMakeTwosComplement(Bits);
			}

			Elysium::Core::Template::System::int32_t zl = Length - DigitShift;
			if (zl < 0)
			{
				zl = 0;
			}
			Elysium::Core::Template::Container::Vector<LimbType> zd(zl);

			if (SmallShift == 0)
			{
				for (Elysium::Core::Template::System::int32_t i = Length - 1; i >= DigitShift; --i)
				{
					zd[i - DigitShift] = Bits[i];
				}
			}
			else
			{
				Elysium::Core::Template::System::int32_t CarryShift = SignTypeBitWidth - SmallShift;
				Elysium::Core::Template::System::uint32_t Carry = 0;
				for (Elysium::Core::Template::System::int32_t i = Length - 1; i >= DigitShift; --i)
				{
					Elysium::Core::Template::System::uint32_t rot = Bits[i];
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

			return BigInteger(zd, IsNegative);
		}
	public:
		inline constexpr BigInteger operator|(const BigInteger& Right)
		{
			if (GetIsZero())
			{
				return Right;
			}
			if (Right.GetIsZero() == 0)
			{
				return *this;
			}

			Elysium::Core::Template::Container::Vector<LimbType> x = ToLimbArray();
			Elysium::Core::Template::Container::Vector<LimbType> y = Right.ToLimbArray();
			Elysium::Core::Template::Container::Vector<LimbType> z(Elysium::Core::Template::Math::Max(x.GetLength(), y.GetLength()));
			LimbType xExtend = _SignOrValue < 0 ? Elysium::Core::Template::Numeric::NumericTraits<LimbType>::Maximum : static_cast<LimbType>(0);
			LimbType yExtend = Right._SignOrValue < 0 ? Elysium::Core::Template::Numeric::NumericTraits<LimbType>::Maximum : static_cast<LimbType>(0);

			for (Elysium::Core::Template::System::size i = 0; i < z.GetLength(); ++i)
			{
				LimbType xu = i < x.GetLength() ? x[i] : xExtend;
				LimbType yu = i < y.GetLength() ? y[i] : yExtend;
				z[i] = xu | yu;
			}

			return BigInteger(z);
		}
	public:
		inline constexpr const SignType GetSign() const noexcept
		{
			return (_SignOrValue > 0) - (_SignOrValue < 0);
		}

		inline constexpr const bool GetIsZero() const noexcept
		{
			return 0 == _SignOrValue;
		}

		inline constexpr const bool GetIsPositive() const noexcept
		{
			return 0 < _SignOrValue;
		}

		inline constexpr const bool GetIsNegative() const noexcept
		{
			return 0 > _SignOrValue;
		}
	public:
		inline static constexpr const BigInteger& Min()
		{
			static const BigInteger Value = BigInteger(-1, Elysium::Core::Template::Container::Vector<LimbType>({ MaskHighBit }));
			return Value;
		}

		inline static constexpr const BigInteger& MinusOne()
		{
			static const BigInteger Value = BigInteger(-1);
			return Value;
		}

		inline static constexpr const BigInteger& Zero()
		{
			static const BigInteger Value = BigInteger(0);
			return Value;
		}
	private:
		inline static const bool GetPartsForBitManipulation(const BigInteger& Value, Elysium::Core::Template::Container::Vector<LimbType>& Bits, SignType& Length)
		{
			if (Value._Limbs.GetLength() == 0)
			{
				if (Value._SignOrValue < 0)
				{
					Bits = { static_cast<uint32_t>(-Value._SignOrValue) };
				}
				else
				{
					Bits = { static_cast<uint32_t>(Value._SignOrValue) };
				}
			}
			else
			{
				Bits = Value._Limbs;
			}
			Length = (Value._Limbs.GetLength() == 0 ? 1 : Value._Limbs.GetLength());

			return Value._SignOrValue < 0;
		}

		// @ToDo: move to Elysium::Core::Numerics::NumericsHelper-class
		inline static const Elysium::Core::Template::Container::Vector<LimbType> DangerousMakeTwosComplement(Elysium::Core::Template::Container::Vector<LimbType>& d)
		{	// first do complement and +1 as long as carry is needed
			SignType i = 0;
			LimbType v = 0;
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

		inline static const Elysium::Core::Template::Container::Vector<LimbType> Resize(Elysium::Core::Template::Container::Vector<LimbType>& Value, 
			const Elysium::Core::Template::System::size Length)
		{
			if (Value.GetLength() == Length)
			{
				return Value;
			}

			Elysium::Core::Template::Container::Vector<LimbType> Result(Length);
			Elysium::Core::Template::System::size NewLength = Elysium::Core::Template::Math::Min(Value.GetLength(), Length);
			for (Elysium::Core::Template::System::size i = 0; i < NewLength; ++i)
			{
				Result[i] = Value[i];
			}
			return Result;
		}

		inline const Elysium::Core::Template::Container::Vector<LimbType> ToLimbArray() const
		{
			if (_Limbs.GetLength() == 0 && _SignOrValue == 0)
			{
				return { 0 };
			}

			Elysium::Core::Template::Container::Vector<LimbType> DWords(0);
			LimbType HighDWord;

			if (_Limbs.GetLength() == 0)
			{
				DWords = { static_cast<LimbType>(_SignOrValue) };
				HighDWord = _SignOrValue < 0 ? Elysium::Core::Template::Numeric::NumericTraits<LimbType>::Maximum : 0;
			}
			else if (_SignOrValue == -1)
			{
				DWords = _Limbs;
				HighDWord = Elysium::Core::Template::Numeric::NumericTraits<LimbType>::Maximum;
			}
			else
			{
				DWords = _Limbs;
				HighDWord = 0;
			}

			// find highest significant byte
			Elysium::Core::Template::System::size msb;
			for (msb = DWords.GetLength() - 1; msb > 0; --msb)
			{
				if (DWords[msb] != HighDWord)
				{
					break;
				}
			}

			// ensure high bit is 0 if positive, 1 if negative
			bool NeedExtraByte = (DWords[msb] & 0x80000000) != (HighDWord & 0x80000000);

			Elysium::Core::Template::Container::Vector<LimbType> Trimmed(msb + 1 + (NeedExtraByte ? 1 : 0));
			Elysium::Core::Template::Memory::MemCpy(&Trimmed[0], &DWords[0], DWords.GetLength());

			if (NeedExtraByte)
			{
				Trimmed[Trimmed.GetLength() - 1] = HighDWord;
			}

			return Trimmed;
		}
	private:
		/// <summary>
		/// Represents the sign of given value.
		/// Also is used as an optimization to store all data if it fits in "SignType".
		/// </summary>
		SignType _SignOrValue;

		/// <summary>
		/// If given value is too large to fit into "SignType", more data is stored here.
		/// </summary>
		Elysium::Core::Template::Container::Vector<LimbType> _Limbs;
	};
}
#endif