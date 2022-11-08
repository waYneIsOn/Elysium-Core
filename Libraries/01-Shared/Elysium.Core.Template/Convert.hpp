/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CONVERT
#define ELYSIUM_CORE_TEMPLATE_TEXT_CONVERT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_ARGUMENTEXCEPTION
#include "../Elysium.Core/ArgumentException.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

#ifndef ELYSIUM_CORE_GLOBALIZATION_NUMBERFORMATINFO
#include "../Elysium.Core.Globalization/NumberFormatInfo.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_CHARACTER
#include "Character.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NUMERIC_NUMERICTRAITS
#include "NumericTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CHARACTERTRAITS
#include "CharacterTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "String.hpp"
#endif

#ifndef _CMATH_
#include <cmath>
#endif

namespace Elysium::Core::Template::Text
{
	template <Concepts::Character C>
	struct Convert
	{
	public:
		using Value = C;
		using Pointer = C*;
		using ConstValue = const C;
		using ConstPointer = const C*;
		using ConstReference = const C&;

		using CorrespondingString = String<C>;
	public:
		Convert() = delete;

		Convert(const Convert& Source) = delete;

		Convert(Convert&& Right) noexcept = delete;

		~Convert() = delete;
	public:
		Convert& operator=(const Convert& Source) = delete;

		Convert& operator=(Convert&& Right) noexcept = delete;
	public:
		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::uint8_t Value, const Elysium::Core::Template::System::uint8_t ToBase,
			const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::uint8_t Value, const Elysium::Core::Template::System::uint8_t ToBase);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::uint8_t Value);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::uint32_t Value, const Elysium::Core::Template::System::uint8_t ToBase,
			const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::uint16_t Value, const Elysium::Core::Template::System::uint8_t ToBase);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::uint16_t Value);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::uint16_t Value, const Elysium::Core::Template::System::uint8_t ToBase,
			const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::uint32_t Value, const Elysium::Core::Template::System::uint8_t ToBase);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::uint32_t Value);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::uint64_t Value, const Elysium::Core::Template::System::uint8_t ToBase,
			const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::uint64_t Value, const Elysium::Core::Template::System::uint8_t ToBase);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::uint64_t Value);

		static Elysium::Core::Template::System::int8_t ToInt8(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase);

		static Elysium::Core::Template::System::int16_t ToInt16(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase);

		static Elysium::Core::Template::System::int32_t ToInt32(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase);

		static Elysium::Core::Template::System::int64_t ToInt64(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase);

		static Elysium::Core::Template::System::uint8_t ToUInt8(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase);

		static Elysium::Core::Template::System::uint16_t ToUInt16(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase);

		static Elysium::Core::Template::System::uint32_t ToUInt32(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase);

		static Elysium::Core::Template::System::uint64_t ToUInt64(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase);
		/*
		static float ToSingle(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase);

		static float ToSingle(ConstPointer Value, const Elysium::Core::Template::System::size Length);

		static float ToSingle(ConstPointer Value);

		static float ToDouble(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase);

		static float ToDouble(ConstPointer Value, const Elysium::Core::Template::System::size Length);

		static float ToDouble(ConstPointer Value);
		*/
	private:
		static const Elysium::Core::Template::System::int32_t ToInt32FromBase2(ConstPointer Value, const Elysium::Core::Template::System::size Length);

		static const Elysium::Core::Template::System::int32_t ToInt32FromBase8(ConstPointer Value, const Elysium::Core::Template::System::size Length);

		static const Elysium::Core::Template::System::int32_t ToInt32FromBase10(ConstPointer Value, const Elysium::Core::Template::System::size Length);

		static const Elysium::Core::Template::System::int32_t ToInt32FromBase16(ConstPointer Value, const Elysium::Core::Template::System::size Length);
	};

	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::System::uint8_t Value, const Elysium::Core::Template::System::uint8_t ToBase, const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo)
	{
		if (ToBase != 2 && ToBase != 8 && ToBase != 10 && ToBase != 16)
		{
			throw Elysium::Core::ArgumentException(u8"ToBase");
		}

		if (Value == 0)
		{
			return "0";
		}

		throw Elysium::Core::NotImplementedException();
	}

	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::System::uint8_t Value, const Elysium::Core::Template::System::uint8_t ToBase)
	{
		return ToString(Value, ToBase, Elysium::Core::Globalization::NumberFormatInfo::GetInvariantInfo());
	}

	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::System::uint8_t Value)
	{
		return ToString(Value, 10, Elysium::Core::Globalization::NumberFormatInfo::GetInvariantInfo());
	}
	
	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::System::uint16_t Value, const Elysium::Core::Template::System::uint8_t ToBase)
	{
		if (ToBase != 2 && ToBase != 8 && ToBase != 10 && ToBase != 16)
		{
			throw Elysium::Core::ArgumentException(u8"ToBase");
		}

		if (Value == 0)
		{
			return "0";
		}

		throw Elysium::Core::NotImplementedException();
	}

	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::System::uint16_t Value, const Elysium::Core::Template::System::uint8_t ToBase, const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo)
	{
		return ToString(Value, ToBase, Elysium::Core::Globalization::NumberFormatInfo::GetInvariantInfo());
	}

	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::System::uint16_t Value)
	{
		return ToString(Value, 10, Elysium::Core::Globalization::NumberFormatInfo::GetInvariantInfo());
	}
	
	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::System::uint32_t Value, const Elysium::Core::Template::System::uint8_t ToBase, const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo)
	{
		if (ToBase != 2 && ToBase != 8 && ToBase != 10 && ToBase != 16)
		{
			throw Elysium::Core::ArgumentException(u8"ToBase");
		}

		if (Value == 0)
		{
			return "0";
		}

		Elysium::Core::Template::System::uint8_t RequiredNumberOfCharacters = 0;
		Elysium::Core::Template::System::uint8_t Index = 0;
		RequiredNumberOfCharacters += static_cast<Elysium::Core::Template::System::uint8_t>(floor(log(Value) / log(ToBase)) + 1_ui8);
		Elysium::Core::Template::Text::Convert<C>::CorrespondingString Result = Elysium::Core::Template::Text::Convert<C>::CorrespondingString(RequiredNumberOfCharacters);

		while (Index < RequiredNumberOfCharacters)
		{
			Elysium::Core::Template::System::int16_t BaseValue = static_cast<Elysium::Core::Template::System::int16_t>(pow(ToBase, static_cast<double>(RequiredNumberOfCharacters) - Index - 1_ui8));
			Elysium::Core::Template::System::int16_t NumericalValue = Value / BaseValue;

			if (NumericalValue < 10)
			{
				Result[Index++] = NumericalValue + static_cast<C>('0');
			}
			else
			{
				Result[Index++] = NumericalValue - 10 + static_cast<C>('A');
			}

			Value -= BaseValue * NumericalValue;
		}

		return Result;
	}

	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::System::uint32_t Value, const Elysium::Core::Template::System::uint8_t ToBase)
	{
		return ToString(Value, ToBase, Elysium::Core::Globalization::NumberFormatInfo::GetInvariantInfo());
	}

	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::System::uint32_t Value)
	{
		return ToString(Value, 10, Elysium::Core::Globalization::NumberFormatInfo::GetInvariantInfo());
	}

	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::System::uint64_t Value, const Elysium::Core::Template::System::uint8_t ToBase, const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo)
	{
		if (ToBase != 2 && ToBase != 8 && ToBase != 10 && ToBase != 16)
		{
			throw Elysium::Core::ArgumentException(u8"ToBase");
		}

		if (Value == 0)
		{
			return "0";
		}

		throw Elysium::Core::NotImplementedException();
	}

	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::System::uint64_t Value, const Elysium::Core::Template::System::uint8_t ToBase)
	{
		return ToString(Value, ToBase, Elysium::Core::Globalization::NumberFormatInfo::GetInvariantInfo());
	}

	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::System::uint64_t Value)
	{
		return ToString(Value, 10, Elysium::Core::Globalization::NumberFormatInfo::GetInvariantInfo());
	}

	template<Concepts::Character C>
	inline Elysium::Core::Template::System::int8_t Convert<C>::ToInt8(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase)
	{
		switch (FromBase)
		{
		/*
		case 2:
			return ToInt8FromBase2(Value, Length);
		case 8:
			return ToInt8FromBase8(Value, Length);
		case 10:
			return ToInt8FromBase10(Value, Length);
		case 16:
			return ToInt8FromBase16(Value, Length);
		*/
		default:
			throw Elysium::Core::ArgumentException(u8"FromBase");
		}
	}

	template<Concepts::Character C>
	inline Elysium::Core::Template::System::int16_t Convert<C>::ToInt16(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase)
	{
		switch (FromBase)
		{
			/*
			case 2:
				return ToInt16FromBase2(Value, Length);
			case 8:
				return ToInt16FromBase2(Value, Length);
			case 10:
				return ToInt16FromBase2(Value, Length);
			case 16:
				return ToInt16FromBase2(Value, Length);
			*/
		default:
			throw Elysium::Core::ArgumentException(u8"FromBase");
		}
	}

	template<Concepts::Character C>
	inline Elysium::Core::Template::System::int32_t Convert<C>::ToInt32(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase)
	{
		switch (FromBase)
		{
		case 2:
			return ToInt32FromBase2(Value, Length);
		case 8:
			return ToInt32FromBase8(Value, Length);
		case 10:
			return ToInt32FromBase10(Value, Length);
		case 16:
			return ToInt32FromBase16(Value, Length);
		default:
			throw Elysium::Core::ArgumentException(u8"FromBase");
		}
	}

	template<Concepts::Character C>
	inline Elysium::Core::Template::System::int64_t Convert<C>::ToInt64(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase)
	{
		switch (FromBase)
		{
			/*
			case 2:
				return ToInt64FromBase2(Value, Length);
			case 8:
				return ToInt64FromBase2(Value, Length);
			case 10:
				return ToInt64FromBase2(Value, Length);
			case 16:
				return ToInt64FromBase2(Value, Length);
			*/
		default:
			throw Elysium::Core::ArgumentException(u8"FromBase");
		}
	}

	template<Concepts::Character C>
	inline Elysium::Core::Template::System::uint8_t Convert<C>::ToUInt8(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase)
	{
		switch (FromBase)
		{
			/*
			case 2:
				return ToUInt8FromBase2(Value, Length);
			case 8:
				return ToUInt8FromBase2(Value, Length);
			case 10:
				return ToUInt8FromBase2(Value, Length);
			case 16:
				return ToUInt8FromBase2(Value, Length);
			*/
		default:
			throw Elysium::Core::ArgumentException(u8"FromBase");
		}
	}

	template<Concepts::Character C>
	inline Elysium::Core::Template::System::uint16_t Convert<C>::ToUInt16(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase)
	{
		switch (FromBase)
		{
			/*
			case 2:
				return ToUInt16FromBase2(Value, Length);
			case 8:
				return ToUInt16FromBase2(Value, Length);
			case 10:
				return ToUInt16FromBase2(Value, Length);
			case 16:
				return ToUInt16FromBase2(Value, Length);
			*/
		default:
			throw Elysium::Core::ArgumentException(u8"FromBase");
		}
	}

	template<Concepts::Character C>
	inline Elysium::Core::Template::System::uint32_t Convert<C>::ToUInt32(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase)
	{
		switch (FromBase)
		{
			/*
			case 2:
				return ToUInt32FromBase2(Value, Length);
			case 8:
				return ToUInt32FromBase2(Value, Length);
			case 10:
				return ToUInt32FromBase2(Value, Length);
			case 16:
				return ToUInt32FromBase2(Value, Length);
			*/
		default:
			throw Elysium::Core::ArgumentException(u8"FromBase");
		}
	}

	template<Concepts::Character C>
	inline Elysium::Core::Template::System::uint64_t Convert<C>::ToUInt64(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase)
	{
		switch (FromBase)
		{
			/*
			case 2:
				return ToUInt64FromBase2(Value, Length);
			case 8:
				return ToUInt64FromBase2(Value, Length);
			case 10:
				return ToUInt64FromBase2(Value, Length);
			case 16:
				return ToUInt64FromBase2(Value, Length);
			*/
		default:
			throw Elysium::Core::ArgumentException(u8"FromBase");
		}
	}

	template<Concepts::Character C>
	inline const Elysium::Core::Template::System::int32_t Convert<C>::ToInt32FromBase2(ConstPointer Value, const Elysium::Core::Template::System::size Length)
	{
		throw Elysium::Core::NotImplementedException();
	}

	template<Concepts::Character C>
	inline const Elysium::Core::Template::System::int32_t Convert<C>::ToInt32FromBase8(ConstPointer Value, const Elysium::Core::Template::System::size Length)
	{
		throw Elysium::Core::NotImplementedException();
	}

	template<Concepts::Character C>
	inline const Elysium::Core::Template::System::int32_t Convert<C>::ToInt32FromBase10(ConstPointer Value, const Elysium::Core::Template::System::size Length)
	{
		// taken from: https://www.geeksforgeeks.org/write-your-own-atoi/
		Elysium::Core::Template::System::int16_t Sign = 1;
		Elysium::Core::Template::System::int32_t i = 0;
		Elysium::Core::Template::System::int32_t Base = 0;
		
		// eat all whitespaces
		while (Value[i] == CharacterTraits<C>::WhitespaceCharacter)
		{
			i++;
		}

		// sign
		if (Value[i] == CharacterTraits<C>::MinusCharacter || Value[i] == CharacterTraits<C>::PlusCharacter)
		{
			Sign = 1 - 2 * (Value[i++] == CharacterTraits<C>::MinusCharacter);
		}

		// ...
		while (Value[i] >= static_cast<ConstValue>('0') && Value[i] <= static_cast<ConstValue>('9') && i < Length)
		{
			// handle overflow cases
			if (Base > Elysium::Core::Template::Numeric::NumericTraits<Elysium::Core::Template::System::int32_t>::Maximum / 10 ||
				(Base == Elysium::Core::Template::Numeric::NumericTraits<Elysium::Core::Template::System::int32_t>::Maximum / 10 && Value[i] - static_cast<ConstValue>('0') > 7))
			{
				return Sign == 1 ? Elysium::Core::Template::Numeric::NumericTraits<Elysium::Core::Template::System::int32_t>::Maximum :
					Elysium::Core::Template::Numeric::NumericTraits<Elysium::Core::Template::System::int32_t>::Minimum;
			}

			Base = 10 * Base + (Value[i++] - static_cast<ConstValue>('0'));
		}

		return Base * Sign;
	}

	template<Concepts::Character C>
	inline const Elysium::Core::Template::System::int32_t Convert<C>::ToInt32FromBase16(ConstPointer Value, const Elysium::Core::Template::System::size Length)
	{
		Elysium::Core::Template::System::int16_t Sign = 1;
		Elysium::Core::Template::System::int32_t i = 0;
		Elysium::Core::Template::System::int32_t Base = 0;

		// eat all whitespaces
		while (Value[i] == CharacterTraits<C>::WhitespaceCharacter)
		{
			i++;
		}

		// sign
		if (Value[i] == CharacterTraits<C>::MinusCharacter || Value[i] == CharacterTraits<C>::PlusCharacter)
		{
			Sign = 1 - 2 * (Value[i++] == CharacterTraits<C>::MinusCharacter);
		}

		// ...
		while (true)
		{
			if (Value[i] >= static_cast<ConstValue>('0') && Value[i] <= static_cast<ConstValue>('9') && i < Length)
			{
				Base = 16 * Base + (Value[i++] - static_cast<ConstValue>('0'));
			}
			else if (Value[i] >= static_cast<ConstValue>('a') && Value[i] <= static_cast<ConstValue>('f') && i < Length)
			{
				Base = 16 * Base + (Value[i++] - static_cast<ConstValue>('a'));
			}
			else if (Value[i] >= static_cast<ConstValue>('A') && Value[i] <= static_cast<ConstValue>('F') && i < Length)
			{
				Base = 16 * Base + (Value[i++] - static_cast<ConstValue>('A'));
			}
			else
			{
				break;
			}
		}

		return Base * Sign;
	}
}
#endif
