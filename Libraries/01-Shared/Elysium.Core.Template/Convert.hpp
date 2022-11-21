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

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_ABSOLUTE
#include "Absolute.hpp"
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
	class Convert
	{
	public:
		using Value = CharacterTraits<C>::Value;
		using Pointer = CharacterTraits<C>::Pointer;
		using ConstValue = CharacterTraits<C>::ConstValue;
		using ConstPointer = CharacterTraits<C>::ConstPointer;
		using ConstReference = CharacterTraits<C>::ConstReference;

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

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::uint16_t Value, const Elysium::Core::Template::System::uint8_t ToBase,
			const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::uint16_t Value, const Elysium::Core::Template::System::uint8_t ToBase);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::uint16_t Value);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::uint32_t Value, const Elysium::Core::Template::System::uint8_t ToBase,
			const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::uint32_t Value, const Elysium::Core::Template::System::uint8_t ToBase);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::uint32_t Value);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::uint64_t Value, const Elysium::Core::Template::System::uint8_t ToBase,
			const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::uint64_t Value, const Elysium::Core::Template::System::uint8_t ToBase);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::uint64_t Value);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::int8_t Value, const Elysium::Core::Template::System::uint8_t ToBase,
			const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::int8_t Value, const Elysium::Core::Template::System::uint8_t ToBase);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::int8_t Value);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::int16_t Value, const Elysium::Core::Template::System::uint8_t ToBase,
			const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::int16_t Value, const Elysium::Core::Template::System::uint8_t ToBase);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::int16_t Value);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::int32_t Value, const Elysium::Core::Template::System::uint8_t ToBase,
			const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::int32_t Value, const Elysium::Core::Template::System::uint8_t ToBase);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::int32_t Value);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::int64_t Value, const Elysium::Core::Template::System::uint8_t ToBase,
			const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::int64_t Value, const Elysium::Core::Template::System::uint8_t ToBase);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::int64_t Value);

		static const typename Convert<C>::CorrespondingString ToString(const float Value, const Elysium::Core::Template::System::uint8_t ToBase,
			const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo);

		static const typename Convert<C>::CorrespondingString ToString(const float Value, const Elysium::Core::Template::System::uint8_t ToBase);

		static const typename Convert<C>::CorrespondingString ToString(const float Value);

		static const typename Convert<C>::CorrespondingString ToString(const double Value, const Elysium::Core::Template::System::uint8_t ToBase,
			const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo);

		static const typename Convert<C>::CorrespondingString ToString(const double Value, const Elysium::Core::Template::System::uint8_t ToBase);

		static const typename Convert<C>::CorrespondingString ToString(const double Value);
	public:
		static Elysium::Core::Template::System::uint8_t ToUInt8(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase,
			const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo);

		static Elysium::Core::Template::System::uint8_t ToUInt8(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase);

		static Elysium::Core::Template::System::uint8_t ToUInt8(ConstPointer Value, const Elysium::Core::Template::System::size Length);

		static Elysium::Core::Template::System::uint16_t ToUInt16(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase,
			const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo);

		static Elysium::Core::Template::System::uint16_t ToUInt16(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase);

		static Elysium::Core::Template::System::uint16_t ToUInt16(ConstPointer Value, const Elysium::Core::Template::System::size Length);

		static Elysium::Core::Template::System::uint32_t ToUInt32(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase,
			const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo);

		static Elysium::Core::Template::System::uint32_t ToUInt32(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase);

		static Elysium::Core::Template::System::uint32_t ToUInt32(ConstPointer Value, const Elysium::Core::Template::System::size Length);

		static Elysium::Core::Template::System::uint64_t ToUInt64(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase,
			const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo);

		static Elysium::Core::Template::System::uint64_t ToUInt64(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase);

		static Elysium::Core::Template::System::uint64_t ToUInt64(ConstPointer Value, const Elysium::Core::Template::System::size Length);

		static Elysium::Core::Template::System::int8_t ToInt8(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase,
			const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo);

		static Elysium::Core::Template::System::int8_t ToInt8(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase);

		static Elysium::Core::Template::System::int8_t ToInt8(ConstPointer Value, const Elysium::Core::Template::System::size Length);

		static Elysium::Core::Template::System::int16_t ToInt16(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase,
			const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo);

		static Elysium::Core::Template::System::int16_t ToInt16(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase);

		static Elysium::Core::Template::System::int16_t ToInt16(ConstPointer Value, const Elysium::Core::Template::System::size Length);

		static Elysium::Core::Template::System::int32_t ToInt32(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase,
			const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo);

		static Elysium::Core::Template::System::int32_t ToInt32(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase);

		static Elysium::Core::Template::System::int32_t ToInt32(ConstPointer Value, const Elysium::Core::Template::System::size Length);

		static Elysium::Core::Template::System::int64_t ToInt64(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase,
			const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo);

		static Elysium::Core::Template::System::int64_t ToInt64(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase);

		static Elysium::Core::Template::System::int64_t ToInt64(ConstPointer Value, const Elysium::Core::Template::System::size Length);

		static float ToSingle(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase,
			const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo);

		static float ToSingle(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase);

		static float ToSingle(ConstPointer Value, const Elysium::Core::Template::System::size Length);

		static double ToDouble(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase,
			const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo);

		static double ToDouble(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase);

		static double ToDouble(ConstPointer Value, const Elysium::Core::Template::System::size Length);
	private:
		static const Elysium::Core::Template::System::int32_t ToInt32FromBase2(ConstPointer Value, const Elysium::Core::Template::System::size Length,
			const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo);

		static const Elysium::Core::Template::System::int32_t ToInt32FromBase8(ConstPointer Value, const Elysium::Core::Template::System::size Length,
			const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo);

		static const Elysium::Core::Template::System::int32_t ToInt32FromBase10(ConstPointer Value, const Elysium::Core::Template::System::size Length,
			const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo);

		static const Elysium::Core::Template::System::int32_t ToInt32FromBase16(ConstPointer Value, const Elysium::Core::Template::System::size Length,
			const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo);
	private:
		inline static const Elysium::Core::Globalization::NumberFormatInfo _InvariantInfo = Elysium::Core::Globalization::NumberFormatInfo::GetInvariantInfo();
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
			return Convert<C>::CorrespondingString('\u0030', 1);
		}

		const System::uint8_t RequiredNumberOfCharacters =
			static_cast<Elysium::Core::Template::System::uint8_t>(floor(log(Value) / log(ToBase)) + 1_ui8);
		Text::Convert<C>::CorrespondingString Result = Elysium::Core::Template::Text::Convert<C>::CorrespondingString(RequiredNumberOfCharacters);

		System::uint8_t Index = 0;
		while (Index < RequiredNumberOfCharacters)
		{
			System::int16_t BaseValue = static_cast<Elysium::Core::Template::System::int16_t>(pow(ToBase, 
				static_cast<double>(RequiredNumberOfCharacters) - Index - 1_ui8));
			System::int16_t NumericalValue = Value / BaseValue;

			if (NumericalValue < 10)
			{
				Result[Index++] = NumericalValue + CharacterTraits<C>::ZeroCharacter;
			}
			else
			{
				Result[Index++] = NumericalValue - 10 + CharacterTraits<C>::UpperACharacter;
			}

			Value -= BaseValue * NumericalValue;
		}

		return Result;
	}

	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::System::uint8_t Value, const Elysium::Core::Template::System::uint8_t ToBase)
	{
		return ToString(Value, ToBase, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::System::uint8_t Value)
	{
		return ToString(Value, 10, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::System::uint16_t Value, const Elysium::Core::Template::System::uint8_t ToBase, const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo)
	{
		if (ToBase != 2 && ToBase != 8 && ToBase != 10 && ToBase != 16)
		{
			throw Elysium::Core::ArgumentException(u8"ToBase");
		}

		if (Value == 0)
		{
			return Convert<C>::CorrespondingString('\u0030', 1);
		}

		const System::uint8_t RequiredNumberOfCharacters =
			static_cast<Elysium::Core::Template::System::uint8_t>(floor(log(Value) / log(ToBase)) + 1_ui8);
		Text::Convert<C>::CorrespondingString Result = Elysium::Core::Template::Text::Convert<C>::CorrespondingString(RequiredNumberOfCharacters);

		System::uint8_t Index = 0;
		while (Index < RequiredNumberOfCharacters)
		{
			System::int16_t BaseValue = static_cast<Elysium::Core::Template::System::int16_t>(pow(ToBase, 
				static_cast<double>(RequiredNumberOfCharacters) - Index - 1_ui8));
			System::int16_t NumericalValue = Value / BaseValue;

			if (NumericalValue < 10)
			{
				Result[Index++] = NumericalValue + CharacterTraits<C>::ZeroCharacter;
			}
			else
			{
				Result[Index++] = NumericalValue - 10 + CharacterTraits<C>::UpperACharacter;
			}

			Value -= BaseValue * NumericalValue;
		}

		return Result;
	}

	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::System::uint16_t Value, const Elysium::Core::Template::System::uint8_t ToBase)
	{
		return ToString(Value, ToBase, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::System::uint16_t Value)
	{
		return ToString(Value, 10, _InvariantInfo);
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
			return Convert<C>::CorrespondingString('\u0030', 1);
		}

		const System::uint8_t RequiredNumberOfCharacters =
			static_cast<Elysium::Core::Template::System::uint8_t>(floor(log(Value) / log(ToBase)) + 1_ui8);
		Text::Convert<C>::CorrespondingString Result = Elysium::Core::Template::Text::Convert<C>::CorrespondingString(RequiredNumberOfCharacters);

		System::uint8_t Index = 0;
		while (Index < RequiredNumberOfCharacters)
		{
			System::int16_t BaseValue = static_cast<Elysium::Core::Template::System::int16_t>(pow(ToBase, 
				static_cast<double>(RequiredNumberOfCharacters) - Index - 1_ui8));
			System::int16_t NumericalValue = Value / BaseValue;

			if (NumericalValue < 10)
			{
				Result[Index++] = NumericalValue + CharacterTraits<C>::ZeroCharacter;
			}
			else
			{
				Result[Index++] = NumericalValue - 10 + CharacterTraits<C>::UpperACharacter;
			}

			Value -= BaseValue * NumericalValue;
		}

		return Result;
	}

	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::System::uint32_t Value, const Elysium::Core::Template::System::uint8_t ToBase)
	{
		return ToString(Value, ToBase, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::System::uint32_t Value)
	{
		return ToString(Value, 10, _InvariantInfo);
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
			return Convert<C>::CorrespondingString('\u0030', 1);
		}

		const System::uint8_t RequiredNumberOfCharacters =
			static_cast<Elysium::Core::Template::System::uint8_t>(floor(log(Value) / log(ToBase)) + 1_ui8);
		Text::Convert<C>::CorrespondingString Result = Elysium::Core::Template::Text::Convert<C>::CorrespondingString(RequiredNumberOfCharacters);

		System::uint8_t Index = 0;
		while (Index < RequiredNumberOfCharacters)
		{
			System::int16_t BaseValue = static_cast<Elysium::Core::Template::System::int16_t>(pow(ToBase, 
				static_cast<double>(RequiredNumberOfCharacters) - Index - 1_ui8));
			System::int16_t NumericalValue = Value / BaseValue;

			if (NumericalValue < 10)
			{
				Result[Index++] = NumericalValue + CharacterTraits<C>::ZeroCharacter;
			}
			else
			{
				Result[Index++] = NumericalValue - 10 + CharacterTraits<C>::UpperACharacter;
			}

			Value -= BaseValue * NumericalValue;
		}

		return Result;
	}

	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::System::uint64_t Value, const Elysium::Core::Template::System::uint8_t ToBase)
	{
		return ToString(Value, ToBase, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::System::uint64_t Value)
	{
		return ToString(Value, 10, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::System::int8_t Value, const Elysium::Core::Template::System::uint8_t ToBase, const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo)
	{
		if (ToBase != 2 && ToBase != 8 && ToBase != 10 && ToBase != 16)
		{
			throw Elysium::Core::ArgumentException(u8"ToBase");
		}

		if (Value == 0)
		{
			return Convert<C>::CorrespondingString('\u0030', 1);
		}

		// ToDo: String<C>
		const Elysium::Core::Utf8String NegativeSign = FormatInfo.GetNegativeSign();
		const System::uint8_t NegativeSignLength = Value < 0 ? static_cast<Elysium::Core::uint8_t>(NegativeSign.GetLength()) : 0;
		const System::uint8_t RequiredNumberOfCharacters =
			static_cast<Elysium::Core::Template::System::uint8_t>(floor(log(Math::Absolute(Value)) / log(ToBase)) + 1_ui8);

		Text::Convert<C>::CorrespondingString Result = Template::Text::Convert<C>::CorrespondingString(RequiredNumberOfCharacters + NegativeSignLength);

		if (NegativeSignLength > 0)
		{
			memcpy(&Result[0], (const void*)&NegativeSign[0], NegativeSignLength * CharacterTraits<C>::MinimumByteLength);
			Value = Math::Absolute(Value);
		}

		System::uint8_t Index = 0;
		while (Index < RequiredNumberOfCharacters)
		{
			System::int16_t BaseValue = static_cast<Elysium::Core::Template::System::int16_t>(pow(ToBase,
				static_cast<double>(RequiredNumberOfCharacters) - Index - 1_ui8));
			System::int16_t NumericalValue = Value / BaseValue;

			if (NumericalValue < 10)
			{
				Result[Index + NegativeSignLength] = NumericalValue + CharacterTraits<C>::ZeroCharacter;
				Index++;
			}
			else
			{
				Result[Index + NegativeSignLength] = NumericalValue - 10 + CharacterTraits<C>::UpperACharacter;
				Index++;
			}

			Value -= BaseValue * NumericalValue;
		}

		return Result;
	}

	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::System::int8_t Value, const Elysium::Core::Template::System::uint8_t ToBase)
	{
		return ToString(Value, ToBase, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::System::int8_t Value)
	{
		return ToString(Value, 10, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::System::int16_t Value, const Elysium::Core::Template::System::uint8_t ToBase, const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo)
	{
		if (ToBase != 2 && ToBase != 8 && ToBase != 10 && ToBase != 16)
		{
			throw Elysium::Core::ArgumentException(u8"ToBase");
		}

		if (Value == 0)
		{
			return Convert<C>::CorrespondingString('\u0030', 1);
		}

		// ToDo: String<C>
		const Elysium::Core::Utf8String NegativeSign = FormatInfo.GetNegativeSign();
		const System::uint8_t NegativeSignLength = Value < 0 ? static_cast<Elysium::Core::uint8_t>(NegativeSign.GetLength()) : 0;
		const System::uint8_t RequiredNumberOfCharacters =
			static_cast<Elysium::Core::Template::System::uint8_t>(floor(log(Math::Absolute(Value)) / log(ToBase)) + 1_ui8);

		Text::Convert<C>::CorrespondingString Result = Template::Text::Convert<C>::CorrespondingString(RequiredNumberOfCharacters + NegativeSignLength);

		if (NegativeSignLength > 0)
		{
			memcpy(&Result[0], (const void*)&NegativeSign[0], NegativeSignLength * CharacterTraits<C>::MinimumByteLength);
			Value = Math::Absolute(Value);
		}

		System::uint8_t Index = 0;
		while (Index < RequiredNumberOfCharacters)
		{
			System::int16_t BaseValue = static_cast<Elysium::Core::Template::System::int16_t>(pow(ToBase,
				static_cast<double>(RequiredNumberOfCharacters) - Index - 1_ui8));
			System::int16_t NumericalValue = Value / BaseValue;

			if (NumericalValue < 10)
			{
				Result[Index + NegativeSignLength] = NumericalValue + CharacterTraits<C>::ZeroCharacter;
				Index++;
			}
			else
			{
				Result[Index + NegativeSignLength] = NumericalValue - 10 + CharacterTraits<C>::UpperACharacter;
				Index++;
			}

			Value -= BaseValue * NumericalValue;
		}

		return Result;
	}

	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::System::int16_t Value, const Elysium::Core::Template::System::uint8_t ToBase)
	{
		return ToString(Value, ToBase, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::System::int16_t Value)
	{
		return ToString(Value, 10, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::System::int32_t Value, const Elysium::Core::Template::System::uint8_t ToBase, const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo)
	{
		if (ToBase != 2 && ToBase != 8 && ToBase != 10 && ToBase != 16)
		{
			throw Elysium::Core::ArgumentException(u8"ToBase");
		}

		if (Value == 0)
		{
			return Convert<C>::CorrespondingString('\u0030', 1);
		}

		// ToDo: String<C>
		const Elysium::Core::Utf8String NegativeSign = FormatInfo.GetNegativeSign();
		const System::uint8_t NegativeSignLength = Value < 0 ? static_cast<Elysium::Core::uint8_t>(NegativeSign.GetLength()) : 0;
		const System::uint8_t RequiredNumberOfCharacters =
			static_cast<Elysium::Core::Template::System::uint8_t>(floor(log(Math::Absolute(Value)) / log(ToBase)) + 1_ui8);

		Text::Convert<C>::CorrespondingString Result = Template::Text::Convert<C>::CorrespondingString(RequiredNumberOfCharacters + NegativeSignLength);

		if (NegativeSignLength > 0)
		{
			memcpy(&Result[0], (const void*)&NegativeSign[0], NegativeSignLength * CharacterTraits<C>::MinimumByteLength);
			Value = Math::Absolute(Value);
		}

		System::uint8_t Index = 0;
		while (Index < RequiredNumberOfCharacters)
		{
			System::int16_t BaseValue = static_cast<Elysium::Core::Template::System::int16_t>(pow(ToBase,
				static_cast<double>(RequiredNumberOfCharacters) - Index - 1_ui8));
			System::int16_t NumericalValue = Value / BaseValue;

			if (NumericalValue < 10)
			{
				Result[Index + NegativeSignLength] = NumericalValue + CharacterTraits<C>::ZeroCharacter;
				Index++;
			}
			else
			{
				Result[Index + NegativeSignLength] = NumericalValue - 10 + CharacterTraits<C>::UpperACharacter;
				Index++;
			}

			Value -= BaseValue * NumericalValue;
		}

		return Result;
	}

	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::System::int32_t Value, const Elysium::Core::Template::System::uint8_t ToBase)
	{
		return ToString(Value, ToBase, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::System::int32_t Value)
	{
		return ToString(Value, 10, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::System::int64_t Value, const Elysium::Core::Template::System::uint8_t ToBase, const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo)
	{
		if (ToBase != 2 && ToBase != 8 && ToBase != 10 && ToBase != 16)
		{
			throw Elysium::Core::ArgumentException(u8"ToBase");
		}

		if (Value == 0)
		{
			return Convert<C>::CorrespondingString('\u0030', 1);
		}

		// ToDo: String<C>
		const Elysium::Core::Utf8String NegativeSign = FormatInfo.GetNegativeSign();
		const System::uint8_t NegativeSignLength = Value < 0 ? static_cast<Elysium::Core::uint8_t>(NegativeSign.GetLength()) : 0;
		const System::uint8_t RequiredNumberOfCharacters = 
			static_cast<Elysium::Core::Template::System::uint8_t>(floor(log(Math::Absolute(Value)) / log(ToBase)) + 1_ui8);

		Text::Convert<C>::CorrespondingString Result = Template::Text::Convert<C>::CorrespondingString(RequiredNumberOfCharacters + NegativeSignLength);

		if (NegativeSignLength > 0)
		{
			memcpy(&Result[0], (const void*)&NegativeSign[0], NegativeSignLength * CharacterTraits<C>::MinimumByteLength);
			Value = Math::Absolute(Value);
		}

		System::uint8_t Index = 0;
		while (Index < RequiredNumberOfCharacters)
		{
			System::int16_t BaseValue = static_cast<Elysium::Core::Template::System::int16_t>(pow(ToBase,
				static_cast<double>(RequiredNumberOfCharacters) - Index - 1_ui8));
			System::int16_t NumericalValue = Value / BaseValue;

			if (NumericalValue < 10)
			{
				Result[Index + NegativeSignLength] = NumericalValue + CharacterTraits<C>::ZeroCharacter;
				Index++;
			}
			else
			{
				Result[Index + NegativeSignLength] = NumericalValue - 10 + CharacterTraits<C>::UpperACharacter;
				Index++;
			}

			Value -= BaseValue * NumericalValue;
		}

		return Result;
	}

	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::System::int64_t Value, const Elysium::Core::Template::System::uint8_t ToBase)
	{
		return ToString(Value, ToBase, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::System::int64_t Value)
	{
		return ToString(Value, 10, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(const float Value, const Elysium::Core::Template::System::uint8_t ToBase, const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo)
	{
		if (ToBase != 2 && ToBase != 8 && ToBase != 10 && ToBase != 16)
		{
			throw Elysium::Core::ArgumentException(u8"ToBase");
		}

		if (Value == 0)
		{
			return Convert<C>::CorrespondingString('\u0030', 1);
		}

		System::int32_t IntegerPart = static_cast<System::int32_t>(Value);

		const Elysium::Core::uint32_t NumberDecimalDigits = 2;
		Elysium::Core::uint32_t FloatingPart = Math::Absolute((Value - IntegerPart) * pow(10, NumberDecimalDigits));

		// ToDo: String<C>
		const Elysium::Core::Utf8String NegativeSign = FormatInfo.GetNegativeSign();
		const Elysium::Core::Utf8String DecimalSeparator = FormatInfo.GetNumberDecimalSeparator();

		const System::uint8_t NegativeSignLength = Value < 0 ? static_cast<Elysium::Core::uint8_t>(NegativeSign.GetLength()) : 0;

		const System::uint8_t RequiredNumberOfCharactersPreFloatingPart =
			static_cast<Elysium::Core::Template::System::uint8_t>(floor(log(Math::Absolute(IntegerPart)) /log(ToBase)) + 1_ui8);

		const System::uint8_t RequiredNumberOfCharactersFloatingPart =
			static_cast<Elysium::Core::Template::System::uint8_t>(floor(log(FloatingPart) / log(ToBase)) + 1_ui8);

		const System::uint8_t DecimalSeparatorLength = RequiredNumberOfCharactersFloatingPart > 0 ?
			static_cast<Elysium::Core::uint8_t>(DecimalSeparator.GetLength()): 0;

		Text::Convert<C>::CorrespondingString Result = Template::Text::Convert<C>::CorrespondingString(NegativeSignLength + 
			RequiredNumberOfCharactersPreFloatingPart + DecimalSeparatorLength + NumberDecimalDigits);

		if (NegativeSignLength > 0)
		{
			memcpy(&Result[0], (const void*)&NegativeSign[0], NegativeSignLength * CharacterTraits<C>::MinimumByteLength);
			IntegerPart = Math::Absolute(IntegerPart);
		}

		System::uint8_t Index = 0;
		while (Index < RequiredNumberOfCharactersPreFloatingPart)
		{
			System::int16_t BaseValue = static_cast<Elysium::Core::Template::System::int16_t>(pow(ToBase,
				static_cast<double>(RequiredNumberOfCharactersPreFloatingPart) - Index - 1_ui8));
			System::int16_t NumericalValue = IntegerPart / BaseValue;

			if (NumericalValue < 10)
			{
				Result[Index + NegativeSignLength] = NumericalValue + CharacterTraits<C>::ZeroCharacter;
				Index++;
			}
			else
			{
				Result[Index + NegativeSignLength] = NumericalValue - 10 + CharacterTraits<C>::UpperACharacter;
				Index++;
			}

			IntegerPart -= BaseValue * NumericalValue;
		}
		
		if (DecimalSeparatorLength > 0)
		{
			memcpy(&Result[Index + NegativeSignLength], (const void*)&DecimalSeparator[0], DecimalSeparatorLength * CharacterTraits<C>::MinimumByteLength);
			Index += DecimalSeparatorLength;
		}

		Index = 0;
		while (Index < RequiredNumberOfCharactersFloatingPart)
		{
			System::int16_t BaseValue = static_cast<Elysium::Core::Template::System::int16_t>(pow(ToBase,
				static_cast<double>(RequiredNumberOfCharactersFloatingPart) - Index - 1_ui8));
			System::int16_t NumericalValue = FloatingPart / BaseValue;

			if (NumericalValue < 10)
			{
				Result[Index + NegativeSignLength + DecimalSeparatorLength + RequiredNumberOfCharactersPreFloatingPart] = 
					NumericalValue + CharacterTraits<C>::ZeroCharacter;
				Index++;
			}
			else
			{
				Result[Index + NegativeSignLength + DecimalSeparatorLength + RequiredNumberOfCharactersPreFloatingPart] = 
					NumericalValue - 10 + CharacterTraits<C>::UpperACharacter;
				Index++;
			}

			if (Index >= NumberDecimalDigits)
			{
				break;
			}

			FloatingPart -= BaseValue * NumericalValue;
		}

		return Result;
	}

	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(const float Value, const Elysium::Core::Template::System::uint8_t ToBase)
	{
		return ToString(Value, ToBase, _InvariantInfo);
	}
	
	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(const float Value)
	{
		return ToString(Value, 10, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(double Value, const Elysium::Core::Template::System::uint8_t ToBase, const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo)
	{
		if (ToBase != 2 && ToBase != 8 && ToBase != 10 && ToBase != 16)
		{
			throw Elysium::Core::ArgumentException(u8"ToBase");
		}

		if (Value == 0)
		{
			return Convert<C>::CorrespondingString('\u0030', 1);
		}

		System::int32_t IntegerPart = static_cast<System::int32_t>(Value);

		const Elysium::Core::uint32_t NumberDecimalDigits = 2;
		Elysium::Core::uint32_t FloatingPart = Math::Absolute((Value - IntegerPart) * pow(10, NumberDecimalDigits));

		// ToDo: String<C>
		const Elysium::Core::Utf8String NegativeSign = FormatInfo.GetNegativeSign();
		const Elysium::Core::Utf8String DecimalSeparator = FormatInfo.GetNumberDecimalSeparator();

		const System::uint8_t NegativeSignLength = Value < 0 ? static_cast<Elysium::Core::uint8_t>(NegativeSign.GetLength()) : 0;

		const System::uint8_t RequiredNumberOfCharactersPreFloatingPart =
			static_cast<Elysium::Core::Template::System::uint8_t>(floor(log(Math::Absolute(IntegerPart)) / log(ToBase)) + 1_ui8);

		const System::uint8_t RequiredNumberOfCharactersFloatingPart =
			static_cast<Elysium::Core::Template::System::uint8_t>(floor(log(FloatingPart) / log(ToBase)) + 1_ui8);

		const System::uint8_t DecimalSeparatorLength = RequiredNumberOfCharactersFloatingPart > 0 ?
			static_cast<Elysium::Core::uint8_t>(DecimalSeparator.GetLength()) : 0;

		Text::Convert<C>::CorrespondingString Result = Template::Text::Convert<C>::CorrespondingString(NegativeSignLength +
			RequiredNumberOfCharactersPreFloatingPart + DecimalSeparatorLength + NumberDecimalDigits);

		if (NegativeSignLength > 0)
		{
			memcpy(&Result[0], (const void*)&NegativeSign[0], NegativeSignLength * CharacterTraits<C>::MinimumByteLength);
			IntegerPart = Math::Absolute(IntegerPart);
		}

		System::uint8_t Index = 0;
		while (Index < RequiredNumberOfCharactersPreFloatingPart)
		{
			System::int16_t BaseValue = static_cast<Elysium::Core::Template::System::int16_t>(pow(ToBase,
				static_cast<double>(RequiredNumberOfCharactersPreFloatingPart) - Index - 1_ui8));
			System::int16_t NumericalValue = IntegerPart / BaseValue;

			if (NumericalValue < 10)
			{
				Result[Index + NegativeSignLength] = NumericalValue + CharacterTraits<C>::ZeroCharacter;
				Index++;
			}
			else
			{
				Result[Index + NegativeSignLength] = NumericalValue - 10 + CharacterTraits<C>::UpperACharacter;
				Index++;
			}

			IntegerPart -= BaseValue * NumericalValue;
		}

		if (DecimalSeparatorLength > 0)
		{
			memcpy(&Result[Index + NegativeSignLength], (const void*)&DecimalSeparator[0], DecimalSeparatorLength * CharacterTraits<C>::MinimumByteLength);
			Index += DecimalSeparatorLength;
		}

		Index = 0;
		while (Index < RequiredNumberOfCharactersFloatingPart)
		{
			System::int16_t BaseValue = static_cast<Elysium::Core::Template::System::int16_t>(pow(ToBase,
				static_cast<double>(RequiredNumberOfCharactersFloatingPart) - Index - 1_ui8));
			System::int16_t NumericalValue = FloatingPart / BaseValue;

			if (NumericalValue < 10)
			{
				Result[Index + NegativeSignLength + DecimalSeparatorLength + RequiredNumberOfCharactersPreFloatingPart] =
					NumericalValue + CharacterTraits<C>::ZeroCharacter;
				Index++;
			}
			else
			{
				Result[Index + NegativeSignLength + DecimalSeparatorLength + RequiredNumberOfCharactersPreFloatingPart] =
					NumericalValue - 10 + CharacterTraits<C>::UpperACharacter;
				Index++;
			}

			if (Index >= NumberDecimalDigits)
			{
				break;
			}

			FloatingPart -= BaseValue * NumericalValue;
		}

		return Result;
	}

	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(double Value, const Elysium::Core::Template::System::uint8_t ToBase)
	{
		return ToString(Value, ToBase, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(double Value)
	{
		return ToString(Value, 10, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline Elysium::Core::Template::System::uint8_t Convert<C>::ToUInt8(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase, const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo)
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
	inline Elysium::Core::Template::System::uint8_t Convert<C>::ToUInt8(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase)
	{
		return ToUInt8(Value, Length, FromBase, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline Elysium::Core::Template::System::uint8_t Convert<C>::ToUInt8(ConstPointer Value, const Elysium::Core::Template::System::size Length)
	{
		return ToUInt8(Value, Length, 10, _InvariantInfo);
	}
	
	template<Concepts::Character C>
	inline Elysium::Core::Template::System::uint16_t Convert<C>::ToUInt16(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase, const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo)
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
	inline Elysium::Core::Template::System::uint16_t Convert<C>::ToUInt16(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase)
	{
		return ToUInt16(Value, Length, FromBase, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline Elysium::Core::Template::System::uint16_t Convert<C>::ToUInt16(ConstPointer Value, const Elysium::Core::Template::System::size Length)
	{
		return ToUInt8(Value, Length, 10, _InvariantInfo);
	}
	
	template<Concepts::Character C>
	inline Elysium::Core::Template::System::uint32_t Convert<C>::ToUInt32(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase, const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo)
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
	inline Elysium::Core::Template::System::uint32_t Convert<C>::ToUInt32(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase)
	{
		return ToUInt32(Value, Length, FromBase, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline Elysium::Core::Template::System::uint32_t Convert<C>::ToUInt32(ConstPointer Value, const Elysium::Core::Template::System::size Length)
	{
		return ToUInt32(Value, Length, 10, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline Elysium::Core::Template::System::uint64_t Convert<C>::ToUInt64(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase, const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo)
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
	inline Elysium::Core::Template::System::uint64_t Convert<C>::ToUInt64(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase)
	{
		return ToUInt64(Value, Length, FromBase, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline Elysium::Core::Template::System::uint64_t Convert<C>::ToUInt64(ConstPointer Value, const Elysium::Core::Template::System::size Length)
	{
		return ToUInt64(Value, Length, 10, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline Elysium::Core::Template::System::int8_t Convert<C>::ToInt8(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase, const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo)
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
	inline Elysium::Core::Template::System::int8_t Convert<C>::ToInt8(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase)
	{
		return ToInt8(Value, Length, FromBase, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline Elysium::Core::Template::System::int8_t Convert<C>::ToInt8(ConstPointer Value, const Elysium::Core::Template::System::size Length)
	{
		return ToInt8(Value, Length, 10, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline Elysium::Core::Template::System::int16_t Convert<C>::ToInt16(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase, const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo)
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
	inline Elysium::Core::Template::System::int16_t Convert<C>::ToInt16(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase)
	{
		return ToInt16(Value, Length, FromBase, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline Elysium::Core::Template::System::int16_t Convert<C>::ToInt16(ConstPointer Value, const Elysium::Core::Template::System::size Length)
	{
		return ToInt16(Value, Length, 10, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline Elysium::Core::Template::System::int32_t Convert<C>::ToInt32(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase, const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo)
	{
		switch (FromBase)
		{
		case 2:
			return ToInt32FromBase2(Value, Length, FormatInfo);
		case 8:
			return ToInt32FromBase8(Value, Length, FormatInfo);
		case 10:
			return ToInt32FromBase10(Value, Length, FormatInfo);
		case 16:
			return ToInt32FromBase16(Value, Length, FormatInfo);
		default:
			throw Elysium::Core::ArgumentException(u8"FromBase");
		}
	}

	template<Concepts::Character C>
	inline Elysium::Core::Template::System::int32_t Convert<C>::ToInt32(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase)
	{
		return ToInt32(Value, Length, FromBase, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline Elysium::Core::Template::System::int32_t Convert<C>::ToInt32(ConstPointer Value, const Elysium::Core::Template::System::size Length)
	{
		return ToInt32(Value, Length, 10, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline Elysium::Core::Template::System::int64_t Convert<C>::ToInt64(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase, const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo)
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
	inline Elysium::Core::Template::System::int64_t Convert<C>::ToInt64(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase)
	{
		return ToInt64(Value, Length, FromBase, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline Elysium::Core::Template::System::int64_t Convert<C>::ToInt64(ConstPointer Value, const Elysium::Core::Template::System::size Length)
	{
		return ToInt64(Value, Length, 10, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline float Convert<C>::ToSingle(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase, const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo)
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
	inline float Convert<C>::ToSingle(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase)
	{
		return ToSingle(Value, Length, FromBase, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline float Convert<C>::ToSingle(ConstPointer Value, const Elysium::Core::Template::System::size Length)
	{
		return ToSingle(Value, Length, 10, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline double Convert<C>::ToDouble(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase, const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo)
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
	inline double Convert<C>::ToDouble(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase)
	{
		return ToDouble(Value, Length, FromBase, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline double Convert<C>::ToDouble(ConstPointer Value, const Elysium::Core::Template::System::size Length)
	{
		return ToDouble(Value, Length, 10, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline const Elysium::Core::Template::System::int32_t Convert<C>::ToInt32FromBase2(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo)
	{
		throw Elysium::Core::NotImplementedException();
	}

	template<Concepts::Character C>
	inline const Elysium::Core::Template::System::int32_t Convert<C>::ToInt32FromBase8(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo)
	{
		throw Elysium::Core::NotImplementedException();
	}

	template<Concepts::Character C>
	inline const Elysium::Core::Template::System::int32_t Convert<C>::ToInt32FromBase10(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo)
	{
		// taken and adapted from: https://www.geeksforgeeks.org/write-your-own-atoi/
		ConstPointer LastCharacter = &Value[Length];

		Elysium::Core::Template::System::int16_t Sign = 1;
		Elysium::Core::Template::System::int32_t Base = 0;
		
		// eat all whitespaces
		while (Value[0] == CharacterTraits<C>::WhitespaceCharacter)
		{
			Value++;
		}
		
		// sign
		if (Value[0] == CharacterTraits<C>::MinusCharacter || Value[0] == CharacterTraits<C>::PlusCharacter)
		{
			Sign = 1 - 2 * (Value[0] == CharacterTraits<C>::MinusCharacter);
			Value++;
		}

		// ...
		while (Value[0] >= '\u0030' && Value[0] <= '\u0039' && Value < LastCharacter)
		{
			// handle overflow cases
			if (Base > Elysium::Core::Template::Numeric::NumericTraits<Elysium::Core::Template::System::int32_t>::Maximum / 10 ||
				(Base == Elysium::Core::Template::Numeric::NumericTraits<Elysium::Core::Template::System::int32_t>::Maximum / 10 && Value[0] - static_cast<ConstValue>('0') > 7))
			{
				return Sign == 1 ? Elysium::Core::Template::Numeric::NumericTraits<Elysium::Core::Template::System::int32_t>::Maximum :
					Elysium::Core::Template::Numeric::NumericTraits<Elysium::Core::Template::System::int32_t>::Minimum;
			}

			Base = 10 * Base + (Value[0] - CharacterTraits<C>::ZeroCharacter);
			Value++;
		}

		return Base * Sign;
	}

	template<Concepts::Character C>
	inline const Elysium::Core::Template::System::int32_t Convert<C>::ToInt32FromBase16(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo)
	{
		// taken and adapted from: https://www.geeksforgeeks.org/write-your-own-atoi/
		ConstPointer LastCharacter = &Value[Length];

		Elysium::Core::Template::System::int16_t Sign = 1;
		Elysium::Core::Template::System::int32_t Base = 0;
		
		// eat all whitespaces
		while (Value[0] == CharacterTraits<C>::WhitespaceCharacter)
		{
			Value++;
		}
		
		// sign
		if (Value[0] == CharacterTraits<C>::MinusCharacter || Value[0] == CharacterTraits<C>::PlusCharacter)
		{
			Sign = 1 - 2 * (Value[0] == CharacterTraits<C>::MinusCharacter);
			Value++;
		}

		// ...
		while (Value < LastCharacter)
		{
			ConstReference CurrentCharacter = Value[0];
			if (CharacterTraits<C>::IsDigit(CurrentCharacter))
			{
				Base = 16 * Base + (CurrentCharacter - CharacterTraits<C>::ZeroCharacter);
			}
			else if (CharacterTraits<C>::IsAsciiHexDigitLower(CurrentCharacter))
			{
				Base = 16 * Base + (CurrentCharacter - CharacterTraits<C>::LowerACharacter);
			}
			else if (CharacterTraits<C>::IsAsciiHexDigitUpper(CurrentCharacter))
			{
				Base = 16 * Base + (CurrentCharacter - CharacterTraits<C>::UpperACharacter);
			}
			else
			{	// we are still within range but CurrentCharacter is no hex digit character
				break;
			}
			Value++;
		}

		return Base * Sign;
	}
}
#endif
