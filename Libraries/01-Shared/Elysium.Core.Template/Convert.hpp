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

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_CHARACTER
#include "Character.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_NUMBERFORMATINFO
#include "NumberFormatInfo.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_ABSOLUTE
#include "Absolute.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_CEILING
#include "Ceiling.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_FLOOR
#include "Floor.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_LOGARITHM
#include "Logarithm.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_DECIMAL
#include "Decimal.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_POWER
#include "Power.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_TRUNCATE
#include "Truncate.hpp"
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

		using CorrespondingNumberFormatInfo = Globalization::NumberFormatInfo<C>;
	public:
		Convert() = delete;

		Convert(const Convert& Source) = delete;

		Convert(Convert&& Right) noexcept = delete;

		~Convert() = delete;
	public:
		Convert& operator=(const Convert& Source) = delete;

		Convert& operator=(Convert&& Right) noexcept = delete;
	public:
		static const typename Convert<C>::CorrespondingString ToHexString(const Elysium::Core::Template::System::byte* Value,
			const Elysium::Core::Template::System::size Size, const CorrespondingNumberFormatInfo& FormatInfo);

		static const typename Convert<C>::CorrespondingString ToHexString(const Elysium::Core::Template::System::byte* Value,
			const Elysium::Core::Template::System::size Length);
	public:
		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::uint8_t Value, const Elysium::Core::Template::System::uint8_t ToBase,
			const CorrespondingNumberFormatInfo& FormatInfo);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::uint8_t Value, const Elysium::Core::Template::System::uint8_t ToBase);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::uint8_t Value);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::uint16_t Value, const Elysium::Core::Template::System::uint8_t ToBase,
			const CorrespondingNumberFormatInfo& FormatInfo);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::uint16_t Value, const Elysium::Core::Template::System::uint8_t ToBase);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::uint16_t Value);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::uint32_t Value, const Elysium::Core::Template::System::uint8_t ToBase,
			const CorrespondingNumberFormatInfo& FormatInfo);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::uint32_t Value, const Elysium::Core::Template::System::uint8_t ToBase);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::uint32_t Value);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::uint64_t Value, const Elysium::Core::Template::System::uint8_t ToBase,
			const CorrespondingNumberFormatInfo& FormatInfo);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::uint64_t Value, const Elysium::Core::Template::System::uint8_t ToBase);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::uint64_t Value);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::int8_t Value, const Elysium::Core::Template::System::uint8_t ToBase,
			const CorrespondingNumberFormatInfo& FormatInfo);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::int8_t Value, const Elysium::Core::Template::System::uint8_t ToBase);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::int8_t Value);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::int16_t Value, const Elysium::Core::Template::System::uint8_t ToBase,
			const CorrespondingNumberFormatInfo& FormatInfo);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::int16_t Value, const Elysium::Core::Template::System::uint8_t ToBase);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::int16_t Value);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::int32_t Value, const Elysium::Core::Template::System::uint8_t ToBase,
			const CorrespondingNumberFormatInfo& FormatInfo);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::int32_t Value, const Elysium::Core::Template::System::uint8_t ToBase);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::int32_t Value);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::int64_t Value, const Elysium::Core::Template::System::uint8_t ToBase,
			const CorrespondingNumberFormatInfo& FormatInfo);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::int64_t Value, const Elysium::Core::Template::System::uint8_t ToBase);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::System::int64_t Value);

		static const typename Convert<C>::CorrespondingString ToString(const float Value, const Elysium::Core::Template::System::uint8_t ToBase,
			const CorrespondingNumberFormatInfo& FormatInfo);

		static const typename Convert<C>::CorrespondingString ToString(const float Value, const Elysium::Core::Template::System::uint8_t ToBase);

		static const typename Convert<C>::CorrespondingString ToString(const float Value);

		static const typename Convert<C>::CorrespondingString ToString(const double Value, const Elysium::Core::Template::System::uint8_t ToBase,
			const CorrespondingNumberFormatInfo& FormatInfo);

		static const typename Convert<C>::CorrespondingString ToString(const double Value, const Elysium::Core::Template::System::uint8_t ToBase);

		static const typename Convert<C>::CorrespondingString ToString(const double Value);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::Math::Decimal Value, const Elysium::Core::Template::System::uint8_t ToBase,
			const CorrespondingNumberFormatInfo& FormatInfo);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::Math::Decimal Value, const Elysium::Core::Template::System::uint8_t ToBase);

		static const typename Convert<C>::CorrespondingString ToString(Elysium::Core::Template::Math::Decimal Value);
	public:
		static Elysium::Core::Template::System::uint8_t ToUInt8(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase,
			const CorrespondingNumberFormatInfo& FormatInfo);

		static Elysium::Core::Template::System::uint8_t ToUInt8(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase);

		static Elysium::Core::Template::System::uint8_t ToUInt8(ConstPointer Value, const Elysium::Core::Template::System::size Length);

		static Elysium::Core::Template::System::uint8_t ToUInt8(ConstPointer Value);

		static Elysium::Core::Template::System::uint16_t ToUInt16(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase,
			const CorrespondingNumberFormatInfo& FormatInfo);

		static Elysium::Core::Template::System::uint16_t ToUInt16(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase);

		static Elysium::Core::Template::System::uint16_t ToUInt16(ConstPointer Value, const Elysium::Core::Template::System::size Length);

		static Elysium::Core::Template::System::uint16_t ToUInt16(ConstPointer Value);

		static Elysium::Core::Template::System::uint32_t ToUInt32(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase,
			const CorrespondingNumberFormatInfo& FormatInfo);

		static Elysium::Core::Template::System::uint32_t ToUInt32(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase);

		static Elysium::Core::Template::System::uint32_t ToUInt32(ConstPointer Value, const Elysium::Core::Template::System::size Length);

		static Elysium::Core::Template::System::uint32_t ToUInt32(ConstPointer Value);

		static Elysium::Core::Template::System::uint64_t ToUInt64(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase,
			const CorrespondingNumberFormatInfo& FormatInfo);

		static Elysium::Core::Template::System::uint64_t ToUInt64(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase);

		static Elysium::Core::Template::System::uint64_t ToUInt64(ConstPointer Value, const Elysium::Core::Template::System::size Length);

		static Elysium::Core::Template::System::uint64_t ToUInt64(ConstPointer Value);

		static Elysium::Core::Template::System::int8_t ToInt8(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase,
			const CorrespondingNumberFormatInfo& FormatInfo);

		static Elysium::Core::Template::System::int8_t ToInt8(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase);

		static Elysium::Core::Template::System::int8_t ToInt8(ConstPointer Value, const Elysium::Core::Template::System::size Length);

		static Elysium::Core::Template::System::int8_t ToInt8(ConstPointer Value);

		static Elysium::Core::Template::System::int16_t ToInt16(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase,
			const CorrespondingNumberFormatInfo& FormatInfo);

		static Elysium::Core::Template::System::int16_t ToInt16(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase);

		static Elysium::Core::Template::System::int16_t ToInt16(ConstPointer Value, const Elysium::Core::Template::System::size Length);

		static Elysium::Core::Template::System::int16_t ToInt16(ConstPointer Value);

		static Elysium::Core::Template::System::int32_t ToInt32(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase,
			const CorrespondingNumberFormatInfo& FormatInfo);

		static Elysium::Core::Template::System::int32_t ToInt32(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase);

		static Elysium::Core::Template::System::int32_t ToInt32(ConstPointer Value, const Elysium::Core::Template::System::size Length);

		static Elysium::Core::Template::System::int32_t ToInt32(ConstPointer Value);

		static Elysium::Core::Template::System::int64_t ToInt64(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase,
			const CorrespondingNumberFormatInfo& FormatInfo);

		static Elysium::Core::Template::System::int64_t ToInt64(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase);

		static Elysium::Core::Template::System::int64_t ToInt64(ConstPointer Value, const Elysium::Core::Template::System::size Length);

		static Elysium::Core::Template::System::int64_t ToInt64(ConstPointer Value);

		static float ToSingle(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase,
			const CorrespondingNumberFormatInfo& FormatInfo);

		static float ToSingle(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase);

		static float ToSingle(ConstPointer Value, const Elysium::Core::Template::System::size Length);

		static float ToSingle(ConstPointer Value);

		static double ToDouble(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase,
			const CorrespondingNumberFormatInfo& FormatInfo);

		static double ToDouble(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase);

		static double ToDouble(ConstPointer Value, const Elysium::Core::Template::System::size Length);

		static double ToDouble(ConstPointer Value);
	private:
		inline static const CorrespondingNumberFormatInfo _InvariantInfo = CorrespondingNumberFormatInfo::GetInvariantInfo();

		inline static constexpr const Elysium::Core::Template::System::byte _HexMap[] =
			{ 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66 };	// lower case
			//{ 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46 };	// upper case
	};

	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToHexString(const Elysium::Core::Template::System::byte* Value, const Elysium::Core::Template::System::size Size, const CorrespondingNumberFormatInfo& FormatInfo)
	{	// original implementation from: https://stackoverflow.com/questions/311165/how-do-you-convert-a-byte-array-to-a-hexadecimal-string-and-vice-versa
		// @ToDo: make use of FormatInfo

		Convert<C>::CorrespondingString Result = Convert<C>::CorrespondingString(Size * 2);

		for (Elysium::Core::Template::System::size i = 0; i < Size; i++)
		{
			Result[i * 2] = _HexMap[(Value[i] & 0xF0) >> 4];
			Result[i * 2 + 1] = _HexMap[Value[i] & 0x0F];
		}

		return Result;
	}

	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToHexString(const Elysium::Core::Template::System::byte* Value, const Elysium::Core::Template::System::size Size)
	{
		return ToHexString(Value, Size, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::System::uint8_t Value, const Elysium::Core::Template::System::uint8_t ToBase, const CorrespondingNumberFormatInfo& FormatInfo)
	{
		if (Value == 0)
		{
			return Convert<C>::CorrespondingString('\u0030', 1);
		}

		const System::uint8_t RequiredNumberOfCharacters =
			static_cast<Elysium::Core::Template::System::uint8_t>(Math::Floor(Math::Logarithm10(Value) / Math::Logarithm10(ToBase)) + 1_ui8);
		Text::Convert<C>::CorrespondingString Result = Elysium::Core::Template::Text::Convert<C>::CorrespondingString(RequiredNumberOfCharacters);

		System::uint8_t Index = 0;
		while (Index < RequiredNumberOfCharacters)
		{
			System::uint8_t BaseValue = static_cast<Elysium::Core::Template::System::uint8_t>(Math::Power(ToBase,
				static_cast<double>(RequiredNumberOfCharacters) - Index - 1_ui8));
			System::uint8_t NumericalValue = Value / BaseValue;

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
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::System::uint16_t Value, const Elysium::Core::Template::System::uint8_t ToBase, const CorrespondingNumberFormatInfo& FormatInfo)
	{
		if (Value == 0)
		{
			return Convert<C>::CorrespondingString('\u0030', 1);
		}

		const System::uint8_t RequiredNumberOfCharacters =
			static_cast<Elysium::Core::Template::System::uint8_t>(Math::Floor(Math::Logarithm10(Value) / Math::Logarithm10(ToBase)) + 1_ui8);
		Text::Convert<C>::CorrespondingString Result = Elysium::Core::Template::Text::Convert<C>::CorrespondingString(RequiredNumberOfCharacters);

		System::uint8_t Index = 0;
		while (Index < RequiredNumberOfCharacters)
		{
			System::uint16_t BaseValue = static_cast<Elysium::Core::Template::System::uint16_t>(Math::Power(ToBase,
				static_cast<double>(RequiredNumberOfCharacters) - Index - 1_ui8));
			System::uint16_t NumericalValue = Value / BaseValue;

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
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::System::uint32_t Value, const Elysium::Core::Template::System::uint8_t ToBase, const CorrespondingNumberFormatInfo& FormatInfo)
	{
		if (Value == 0)
		{
			return Convert<C>::CorrespondingString('\u0030', 1);
		}

		const System::uint8_t RequiredNumberOfCharacters =
			static_cast<Elysium::Core::Template::System::uint8_t>(Math::Floor(Math::Logarithm10(Value) / Math::Logarithm10(ToBase)) + 1_ui8);
		Text::Convert<C>::CorrespondingString Result = Elysium::Core::Template::Text::Convert<C>::CorrespondingString(RequiredNumberOfCharacters);

		System::uint8_t Index = 0;
		while (Index < RequiredNumberOfCharacters)
		{
			System::uint32_t BaseValue = static_cast<Elysium::Core::Template::System::uint32_t>(Math::Power(ToBase,
				static_cast<double>(RequiredNumberOfCharacters) - Index - 1_ui8));
			System::uint32_t NumericalValue = Value / BaseValue;

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
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::System::uint64_t Value, const Elysium::Core::Template::System::uint8_t ToBase, const CorrespondingNumberFormatInfo& FormatInfo)
	{
		if (Value == 0)
		{
			return Convert<C>::CorrespondingString('\u0030', 1);
		}

		const System::uint8_t RequiredNumberOfCharacters =
			static_cast<Elysium::Core::Template::System::uint8_t>(Math::Floor(Math::Logarithm10(Value) / Math::Logarithm10(ToBase)) + 1_ui8);
		Text::Convert<C>::CorrespondingString Result = Elysium::Core::Template::Text::Convert<C>::CorrespondingString(RequiredNumberOfCharacters);

		System::uint8_t Index = 0;
		while (Index < RequiredNumberOfCharacters)
		{
			System::uint64_t BaseValue = static_cast<Elysium::Core::Template::System::uint64_t>(Math::Power(ToBase,
				static_cast<double>(RequiredNumberOfCharacters) - Index - 1_ui8));
			System::uint32_t NumericalValue = static_cast<System::uint32_t>(Value / BaseValue);

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
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::System::int8_t Value, const Elysium::Core::Template::System::uint8_t ToBase, const CorrespondingNumberFormatInfo& FormatInfo)
	{
		if (Value == 0)
		{
			return Convert<C>::CorrespondingString('\u0030', 1);
		}

		const CorrespondingString NegativeSign = FormatInfo.GetNegativeSign();
		const System::uint8_t NegativeSignLength = Value < 0 ? static_cast<Elysium::Core::uint8_t>(NegativeSign.GetLength()) : 0;
		const System::uint8_t RequiredNumberOfCharacters =
			static_cast<Elysium::Core::Template::System::uint8_t>(Math::Floor(Math::Logarithm(Math::Absolute(Value)) / Math::Logarithm(ToBase)) + 1_ui8);

		Text::Convert<C>::CorrespondingString Result = Template::Text::Convert<C>::CorrespondingString(RequiredNumberOfCharacters + NegativeSignLength);

		if (NegativeSignLength > 0)
		{
			memcpy(&Result[0], (const void*)&NegativeSign[0], NegativeSignLength * CharacterTraits<C>::MinimumByteLength);
			Value = Math::Absolute(Value);
		}

		System::uint8_t Index = 0;
		while (Index < RequiredNumberOfCharacters)
		{
			System::uint8_t BaseValue = static_cast<Elysium::Core::Template::System::uint8_t>(Math::Power(ToBase,
				static_cast<double>(RequiredNumberOfCharacters) - Index - 1_ui8));
			System::uint8_t NumericalValue = Value / BaseValue;

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
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::System::int16_t Value, const Elysium::Core::Template::System::uint8_t ToBase, const CorrespondingNumberFormatInfo& FormatInfo)
	{
		if (Value == 0)
		{
			return Convert<C>::CorrespondingString('\u0030', 1);
		}

		const CorrespondingString NegativeSign = FormatInfo.GetNegativeSign();
		const System::uint8_t NegativeSignLength = Value < 0 ? static_cast<Elysium::Core::uint8_t>(NegativeSign.GetLength()) : 0;
		const System::uint8_t RequiredNumberOfCharacters =
			static_cast<Elysium::Core::Template::System::uint8_t>(Math::Floor(Math::Logarithm(Math::Absolute(Value)) / Math::Logarithm(ToBase)) + 1_ui8);

		Text::Convert<C>::CorrespondingString Result = Template::Text::Convert<C>::CorrespondingString(RequiredNumberOfCharacters + NegativeSignLength);

		if (NegativeSignLength > 0)
		{
			memcpy(&Result[0], (const void*)&NegativeSign[0], NegativeSignLength * CharacterTraits<C>::MinimumByteLength);
			Value = Math::Absolute(Value);
		}

		System::uint8_t Index = 0;
		while (Index < RequiredNumberOfCharacters)
		{
			System::uint16_t BaseValue = static_cast<Elysium::Core::Template::System::uint16_t>(Math::Power(ToBase,
				static_cast<double>(RequiredNumberOfCharacters) - Index - 1_ui8));
			System::uint16_t NumericalValue = Value / BaseValue;

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
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::System::int32_t Value, const Elysium::Core::Template::System::uint8_t ToBase, const CorrespondingNumberFormatInfo& FormatInfo)
	{
		if (Value == 0)
		{
			return Convert<C>::CorrespondingString('\u0030', 1);
		}

		const CorrespondingString NegativeSign = FormatInfo.GetNegativeSign();
		const System::uint8_t NegativeSignLength = Value < 0 ? static_cast<Elysium::Core::uint8_t>(NegativeSign.GetLength()) : 0;
		const System::uint8_t RequiredNumberOfCharacters =
			static_cast<Elysium::Core::Template::System::uint8_t>(Math::Floor(Math::Logarithm(Math::Absolute(Value)) / Math::Logarithm(ToBase)) + 1_ui8);

		Text::Convert<C>::CorrespondingString Result = Template::Text::Convert<C>::CorrespondingString(RequiredNumberOfCharacters + NegativeSignLength);

		if (NegativeSignLength > 0)
		{
			memcpy(&Result[0], (const void*)&NegativeSign[0], NegativeSignLength * CharacterTraits<C>::MinimumByteLength);
			Value = Math::Absolute(Value);
		}

		System::uint8_t Index = 0;
		while (Index < RequiredNumberOfCharacters)
		{
			System::uint32_t BaseValue = static_cast<Elysium::Core::Template::System::uint32_t>(Math::Power(ToBase,
				static_cast<double>(RequiredNumberOfCharacters) - Index - 1_ui8));
			System::uint32_t NumericalValue = Value / BaseValue;

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
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::System::int64_t Value, const Elysium::Core::Template::System::uint8_t ToBase, const CorrespondingNumberFormatInfo& FormatInfo)
	{
		if (Value == 0)
		{
			return Convert<C>::CorrespondingString('\u0030', 1);
		}

		const CorrespondingString NegativeSign = FormatInfo.GetNegativeSign();
		const System::uint8_t NegativeSignLength = Value < 0 ? static_cast<Elysium::Core::uint8_t>(NegativeSign.GetLength()) : 0;
		const System::uint8_t RequiredNumberOfCharacters = 
			static_cast<Elysium::Core::Template::System::uint8_t>(Math::Floor(Math::Logarithm(Math::Absolute(Value)) / Math::Logarithm(ToBase)) + 1_ui8);

		Text::Convert<C>::CorrespondingString Result = Template::Text::Convert<C>::CorrespondingString(RequiredNumberOfCharacters + NegativeSignLength);

		if (NegativeSignLength > 0)
		{
			memcpy(&Result[0], (const void*)&NegativeSign[0], NegativeSignLength * CharacterTraits<C>::MinimumByteLength);
			Value = Math::Absolute(Value);
		}

		System::uint8_t Index = 0;
		while (Index < RequiredNumberOfCharacters)
		{
			System::uint64_t BaseValue = static_cast<Elysium::Core::Template::System::uint64_t>(Math::Power(ToBase,
				static_cast<double>(RequiredNumberOfCharacters) - Index - 1_ui8));
			System::uint32_t NumericalValue = static_cast<System::uint32_t>(Value / BaseValue);

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
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(const float Value, const Elysium::Core::Template::System::uint8_t ToBase, const CorrespondingNumberFormatInfo& FormatInfo)
	{
		if (Value == 0)
		{
			return Convert<C>::CorrespondingString('\u0030', 1);
		}

		const System::uint32_t NumberDecimalDigits = 2;
		System::int32_t IntegerPart = Math::Truncate<float, System::int32_t>(Value);
		System::uint32_t FloatingPart = 
			static_cast<System::uint32_t>(Math::Ceiling(Math::Absolute(Value - IntegerPart) * Math::Power(10, NumberDecimalDigits)));

		const CorrespondingString NegativeSign = FormatInfo.GetNegativeSign();
		const CorrespondingString DecimalSeparator = FormatInfo.GetNumberDecimalSeparator();

		const System::uint8_t NegativeSignLength = Value < 0 ? static_cast<Elysium::Core::uint8_t>(NegativeSign.GetLength()) : 0;

		const System::uint8_t RequiredNumberOfCharactersPreFloatingPart =
			static_cast<Elysium::Core::Template::System::uint8_t>(Math::Floor(Math::Logarithm(Math::Absolute(IntegerPart)) / Math::Logarithm(ToBase)) + 1_ui8);

		const System::uint8_t RequiredNumberOfCharactersFloatingPart =
			static_cast<Elysium::Core::Template::System::uint8_t>(Math::Floor(Math::Logarithm(FloatingPart) / Math::Logarithm(ToBase)) + 1_ui8);

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
			System::int16_t BaseValue = static_cast<Elysium::Core::Template::System::int16_t>(Math::Power(ToBase,
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
			System::int16_t BaseValue = static_cast<Elysium::Core::Template::System::int16_t>(Math::Power(ToBase,
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
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(double Value, const Elysium::Core::Template::System::uint8_t ToBase, const CorrespondingNumberFormatInfo& FormatInfo)
	{
		if (Value == 0)
		{
			return Convert<C>::CorrespondingString('\u0030', 1);
		}

		const System::uint64_t NumberDecimalDigits = 2;
		System::int32_t IntegerPart = Math::Truncate<double, System::int32_t>(Value);
		System::uint64_t FloatingPart =
			static_cast<System::uint64_t>(Math::Ceiling(Math::Absolute(Value - IntegerPart) * Math::Power(10, NumberDecimalDigits)));
		
		const CorrespondingString NegativeSign = FormatInfo.GetNegativeSign();
		const CorrespondingString DecimalSeparator = FormatInfo.GetNumberDecimalSeparator();

		const System::uint8_t NegativeSignLength = Value < 0 ? static_cast<Elysium::Core::uint8_t>(NegativeSign.GetLength()) : 0;

		const System::uint8_t RequiredNumberOfCharactersPreFloatingPart =
			static_cast<Elysium::Core::Template::System::uint8_t>(Math::Floor(Math::Logarithm(Math::Absolute(IntegerPart)) / Math::Logarithm(ToBase)) + 1_ui8);

		const System::uint8_t RequiredNumberOfCharactersFloatingPart =
			static_cast<Elysium::Core::Template::System::uint8_t>(Math::Floor(Math::Logarithm(FloatingPart) / Math::Logarithm(ToBase)) + 1_ui8);

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
			System::int16_t BaseValue = static_cast<Elysium::Core::Template::System::int16_t>(Math::Power(ToBase,
				static_cast<double>(RequiredNumberOfCharactersPreFloatingPart) - Index - 1_ui8));
			System::int16_t NumericalValue = static_cast<System::int16_t>(IntegerPart / BaseValue);

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
			System::int16_t BaseValue = static_cast<Elysium::Core::Template::System::int16_t>(Math::Power(ToBase,
				static_cast<double>(RequiredNumberOfCharactersFloatingPart) - Index - 1_ui8));
			System::int16_t NumericalValue = static_cast<System::int16_t>(IntegerPart / BaseValue);

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
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::Math::Decimal Value, const Elysium::Core::Template::System::uint8_t ToBase, const CorrespondingNumberFormatInfo& FormatInfo)
	{
		Elysium::Core::Template::System::int64_t HighPart = Value.GetHighPart();
		Elysium::Core::Template::System::uint64_t LowPart = Value.GetLowPart();
		
		if (HighPart == 0 && LowPart == 0)
		{
			return Convert<C>::CorrespondingString('\u0030', 1);
		}

		const System::uint64_t NumberDecimalDigits = 4;

		const CorrespondingString NegativeSign = FormatInfo.GetNegativeSign();
		const CorrespondingString DecimalSeparator = FormatInfo.GetNumberDecimalSeparator();

		const System::uint8_t NegativeSignLength = Value < 0 ? static_cast<Elysium::Core::uint8_t>(NegativeSign.GetLength()) : 0;

		const System::uint8_t RequiredNumberOfCharactersHighPart =
			static_cast<Elysium::Core::Template::System::uint8_t>(Math::Floor(Math::Logarithm(Math::Absolute(HighPart)) / Math::Logarithm(ToBase)) + 1_ui8);

		const System::uint8_t RequiredNumberOfCharactersLowPart =
			static_cast<Elysium::Core::Template::System::uint8_t>(Math::Floor(Math::Logarithm(LowPart) / Math::Logarithm(ToBase)) + 1_ui8);

		const System::uint8_t DecimalSeparatorLength = RequiredNumberOfCharactersLowPart > 0 ?
			static_cast<Elysium::Core::uint8_t>(DecimalSeparator.GetLength()) : 0;

		Text::Convert<C>::CorrespondingString Result = Template::Text::Convert<C>::CorrespondingString(NegativeSignLength +
			RequiredNumberOfCharactersHighPart + DecimalSeparatorLength + NumberDecimalDigits);

		if (NegativeSignLength > 0)
		{
			memcpy(&Result[0], (const void*)&NegativeSign[0], NegativeSignLength * CharacterTraits<C>::MinimumByteLength);
			HighPart = Math::Absolute(HighPart);
		}

		System::uint8_t Index = 0;
		while (Index < RequiredNumberOfCharactersHighPart)
		{
			System::int16_t BaseValue = static_cast<Elysium::Core::Template::System::int16_t>(Math::Power(ToBase,
				static_cast<double>(RequiredNumberOfCharactersHighPart) - Index - 1_ui8));
			System::int16_t NumericalValue = HighPart / BaseValue;

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

			HighPart -= BaseValue * NumericalValue;
		}

		if (DecimalSeparatorLength > 0)
		{
			memcpy(&Result[Index + NegativeSignLength], (const void*)&DecimalSeparator[0], DecimalSeparatorLength * CharacterTraits<C>::MinimumByteLength);
			Index += DecimalSeparatorLength;
		}

		Index = 0;
		while (Index < RequiredNumberOfCharactersLowPart)
		{
			System::int64_t BaseValue = static_cast<Elysium::Core::Template::System::int64_t>(Math::Power(ToBase,
				static_cast<double>(RequiredNumberOfCharactersLowPart) - Index - 1_ui8));
			System::int64_t NumericalValue = LowPart / BaseValue;

			if (NumericalValue < 10)
			{
				Result[Index + NegativeSignLength + DecimalSeparatorLength + RequiredNumberOfCharactersHighPart] =
					NumericalValue + CharacterTraits<C>::ZeroCharacter;
				Index++;
			}
			else
			{
				Result[Index + NegativeSignLength + DecimalSeparatorLength + RequiredNumberOfCharactersHighPart] =
					NumericalValue - 10 + CharacterTraits<C>::UpperACharacter;
				Index++;
			}

			if (Index >= NumberDecimalDigits)
			{
				break;
			}

			LowPart -= BaseValue * NumericalValue;
		}
		
		return Result;
	}

	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::Math::Decimal Value, const Elysium::Core::Template::System::uint8_t ToBase)
	{
		return ToString(Value, ToBase, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline const typename Convert<C>::CorrespondingString Convert<C>::ToString(Elysium::Core::Template::Math::Decimal Value)
	{
		return ToString(Value, 10, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline Elysium::Core::Template::System::uint8_t Convert<C>::ToUInt8(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase, const CorrespondingNumberFormatInfo& FormatInfo)
	{	// taken and adapted from: https://www.geeksforgeeks.org/write-your-own-atoi/
		Pointer ChangeableValue = (Pointer)Value;
		System::uint8_t Result = 0;
		while (ChangeableValue < &Value[Length])
		{
			if (CharacterTraits<C>::IsDigit(ChangeableValue[0]))
			{
				Result = FromBase * Result + static_cast<System::uint8_t>(ChangeableValue[0] - CharacterTraits<C>::ZeroCharacter);
			}
			else if (CharacterTraits<C>::IsAsciiHexDigitLower(ChangeableValue[0]))
			{
				Result = FromBase * Result + static_cast<System::uint8_t>(10_i8 + ChangeableValue[0] - CharacterTraits<C>::LowerACharacter);
			}
			else if (CharacterTraits<C>::IsAsciiHexDigitUpper(ChangeableValue[0]))
			{
				Result = FromBase * Result + static_cast<System::uint8_t>(10_i8 + ChangeableValue[0] - CharacterTraits<C>::UpperACharacter);
			}
			else
			{
				break;
			}
			ChangeableValue++;
		}

		return Result;
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
	inline Elysium::Core::Template::System::uint8_t Convert<C>::ToUInt8(ConstPointer Value)
	{
		return ToUInt8(Value, CharacterTraits<C>::GetLength(Value), 10, _InvariantInfo);
	}
	
	template<Concepts::Character C>
	inline Elysium::Core::Template::System::uint16_t Convert<C>::ToUInt16(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase, const CorrespondingNumberFormatInfo& FormatInfo)
	{	// taken and adapted from: https://www.geeksforgeeks.org/write-your-own-atoi/
		Pointer ChangeableValue = (Pointer)Value;
		System::uint16_t Result = 0;
		while (ChangeableValue < &Value[Length])
		{
			if (CharacterTraits<C>::IsDigit(ChangeableValue[0]))
			{
				Result = FromBase * Result + static_cast<System::uint16_t>(ChangeableValue[0] - CharacterTraits<C>::ZeroCharacter);
			}
			else if (CharacterTraits<C>::IsAsciiHexDigitLower(ChangeableValue[0]))
			{
				Result = FromBase * Result + static_cast<System::uint16_t>(10_i8 + ChangeableValue[0] - CharacterTraits<C>::LowerACharacter);
			}
			else if (CharacterTraits<C>::IsAsciiHexDigitUpper(ChangeableValue[0]))
			{
				Result = FromBase * Result + static_cast<System::uint16_t>(10_i8 + ChangeableValue[0] - CharacterTraits<C>::UpperACharacter);
			}
			else
			{
				break;
			}
			ChangeableValue++;
		}

		return Result;
	}

	template<Concepts::Character C>
	inline Elysium::Core::Template::System::uint16_t Convert<C>::ToUInt16(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase)
	{
		return ToUInt16(Value, Length, FromBase, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline Elysium::Core::Template::System::uint16_t Convert<C>::ToUInt16(ConstPointer Value, const Elysium::Core::Template::System::size Length)
	{
		return ToUInt16(Value, Length, 10, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline Elysium::Core::Template::System::uint16_t Convert<C>::ToUInt16(ConstPointer Value)
	{
		return ToUInt16(Value, CharacterTraits<C>::GetLength(Value), 10, _InvariantInfo);
	}
	
	template<Concepts::Character C>
	inline Elysium::Core::Template::System::uint32_t Convert<C>::ToUInt32(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase, const CorrespondingNumberFormatInfo& FormatInfo)
	{	// taken and adapted from: https://www.geeksforgeeks.org/write-your-own-atoi/
		Pointer ChangeableValue = (Pointer)Value;
		System::uint32_t Result = 0;
		while (ChangeableValue < &Value[Length])
		{
			if (CharacterTraits<C>::IsDigit(ChangeableValue[0]))
			{
				Result = FromBase * Result + (ChangeableValue[0] - CharacterTraits<C>::ZeroCharacter);
			}
			else if (CharacterTraits<C>::IsAsciiHexDigitLower(ChangeableValue[0]))
			{
				Result = FromBase * Result + (10_i8 + ChangeableValue[0] - CharacterTraits<C>::LowerACharacter);
			}
			else if (CharacterTraits<C>::IsAsciiHexDigitUpper(ChangeableValue[0]))
			{
				Result = FromBase * Result + (10_i8 + ChangeableValue[0] - CharacterTraits<C>::UpperACharacter);
			}
			else
			{
				break;
			}
			ChangeableValue++;
		}

		return Result;
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
	inline Elysium::Core::Template::System::uint32_t Convert<C>::ToUInt32(ConstPointer Value)
	{
		return ToUInt32(Value, CharacterTraits<C>::GetLength(Value), 10, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline Elysium::Core::Template::System::uint64_t Convert<C>::ToUInt64(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase, const CorrespondingNumberFormatInfo& FormatInfo)
	{	// taken and adapted from: https://www.geeksforgeeks.org/write-your-own-atoi/
		Pointer ChangeableValue = (Pointer)Value;
		System::uint64_t Result = 0;
		while (ChangeableValue < &Value[Length])
		{
			if (CharacterTraits<C>::IsDigit(ChangeableValue[0]))
			{
				Result = FromBase * Result + (ChangeableValue[0] - CharacterTraits<C>::ZeroCharacter);
			}
			else if (CharacterTraits<C>::IsAsciiHexDigitLower(ChangeableValue[0]))
			{
				Result = FromBase * Result + (10_i8 + ChangeableValue[0] - CharacterTraits<C>::LowerACharacter);
			}
			else if (CharacterTraits<C>::IsAsciiHexDigitUpper(ChangeableValue[0]))
			{
				Result = FromBase * Result + (10_i8 + ChangeableValue[0] - CharacterTraits<C>::UpperACharacter);
			}
			else
			{
				break;
			}
			ChangeableValue++;
		}

		return Result;
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
	inline Elysium::Core::Template::System::uint64_t Convert<C>::ToUInt64(ConstPointer Value)
	{
		return ToUInt64(Value, CharacterTraits<C>::GetLength(Value), 10, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline Elysium::Core::Template::System::int8_t Convert<C>::ToInt8(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase, const CorrespondingNumberFormatInfo& FormatInfo)
	{	// taken and adapted from: https://www.geeksforgeeks.org/write-your-own-atoi/
		Pointer ChangeableValue = (Pointer)Value;
		ConstPointer LastCharacter = &Value[Length];

		// sign
		System::int16_t Sign = 1;
		if (ChangeableValue[0] == CharacterTraits<C>::MinusCharacter || ChangeableValue[0] == CharacterTraits<C>::PlusCharacter)
		{
			Sign = 1 - 2 * (ChangeableValue[0] == CharacterTraits<C>::MinusCharacter);
			ChangeableValue++;
		}

		// ...
		System::int8_t AbsoluteResult = 0;
		while (ChangeableValue < LastCharacter)
		{
			if (CharacterTraits<C>::IsDigit(ChangeableValue[0]))
			{
				AbsoluteResult = FromBase * AbsoluteResult + static_cast<System::int8_t>(ChangeableValue[0] - CharacterTraits<C>::ZeroCharacter);
			}
			else if (CharacterTraits<C>::IsAsciiHexDigitLower(ChangeableValue[0]))
			{
				AbsoluteResult = FromBase * AbsoluteResult + static_cast<System::int8_t>(10_i8 + ChangeableValue[0] - CharacterTraits<C>::LowerACharacter);
			}
			else if (CharacterTraits<C>::IsAsciiHexDigitUpper(ChangeableValue[0]))
			{
				AbsoluteResult = FromBase * AbsoluteResult + static_cast<System::int8_t>(10_i8 + ChangeableValue[0] - CharacterTraits<C>::UpperACharacter);
			}
			else
			{
				break;
			}
			ChangeableValue++;
		}

		return AbsoluteResult * Sign;
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
	inline Elysium::Core::Template::System::int8_t Convert<C>::ToInt8(ConstPointer Value)
	{
		return ToInt8(Value, CharacterTraits<C>::GetLength(Value), 10, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline Elysium::Core::Template::System::int16_t Convert<C>::ToInt16(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase, const CorrespondingNumberFormatInfo& FormatInfo)
	{	// taken and adapted from: https://www.geeksforgeeks.org/write-your-own-atoi/
		Pointer ChangeableValue = (Pointer)Value;
		ConstPointer LastCharacter = &Value[Length];

		// sign
		System::int16_t Sign = 1;
		if (ChangeableValue[0] == CharacterTraits<C>::MinusCharacter || ChangeableValue[0] == CharacterTraits<C>::PlusCharacter)
		{
			Sign = 1 - 2 * (ChangeableValue[0] == CharacterTraits<C>::MinusCharacter);
			ChangeableValue++;
		}

		// ...
		System::int16_t AbsoluteResult = 0;
		while (ChangeableValue < LastCharacter)
		{
			if (CharacterTraits<C>::IsDigit(ChangeableValue[0]))
			{
				AbsoluteResult = FromBase * AbsoluteResult + static_cast<System::int16_t>(ChangeableValue[0] - CharacterTraits<C>::ZeroCharacter);
			}
			else if (CharacterTraits<C>::IsAsciiHexDigitLower(ChangeableValue[0]))
			{
				AbsoluteResult = FromBase * AbsoluteResult + static_cast<System::int16_t>(10_i16 + ChangeableValue[0] - CharacterTraits<C>::LowerACharacter);
			}
			else if (CharacterTraits<C>::IsAsciiHexDigitUpper(ChangeableValue[0]))
			{
				AbsoluteResult = FromBase * AbsoluteResult + static_cast<System::int16_t>(10_i16 + ChangeableValue[0] - CharacterTraits<C>::UpperACharacter);
			}
			else
			{
				break;
			}
			ChangeableValue++;
		}

		return AbsoluteResult * Sign;
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
	inline Elysium::Core::Template::System::int16_t Convert<C>::ToInt16(ConstPointer Value)
	{
		return ToInt16(Value, CharacterTraits<C>::GetLength(Value), 10, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline Elysium::Core::Template::System::int32_t Convert<C>::ToInt32(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase, const CorrespondingNumberFormatInfo& FormatInfo)
	{	// taken and adapted from: https://www.geeksforgeeks.org/write-your-own-atoi/
		Pointer ChangeableValue = (Pointer)Value;
		ConstPointer LastCharacter = &Value[Length];

		// sign
		System::int16_t Sign = 1;
		if (ChangeableValue[0] == CharacterTraits<C>::MinusCharacter || ChangeableValue[0] == CharacterTraits<C>::PlusCharacter)
		{
			Sign = 1 - 2 * (ChangeableValue[0] == CharacterTraits<C>::MinusCharacter);
			ChangeableValue++;
		}

		// ...
		System::int32_t AbsoluteResult = 0;
		while (ChangeableValue < LastCharacter)
		{
			if (CharacterTraits<C>::IsDigit(ChangeableValue[0]))
			{
				AbsoluteResult = FromBase * AbsoluteResult + (ChangeableValue[0] - CharacterTraits<C>::ZeroCharacter);
			}
			else if (CharacterTraits<C>::IsAsciiHexDigitLower(ChangeableValue[0]))
			{
				AbsoluteResult = FromBase * AbsoluteResult + (10 + ChangeableValue[0] - CharacterTraits<C>::LowerACharacter);
			}
			else if (CharacterTraits<C>::IsAsciiHexDigitUpper(ChangeableValue[0]))
			{
				AbsoluteResult = FromBase * AbsoluteResult + (10 + ChangeableValue[0] - CharacterTraits<C>::UpperACharacter);
			}
			else
			{
				break;
			}
			ChangeableValue++;
		}

		return AbsoluteResult * Sign;
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
	inline Elysium::Core::Template::System::int32_t Convert<C>::ToInt32(ConstPointer Value)
	{
		return ToInt32(Value, CharacterTraits<C>::GetLength(Value), 10, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline Elysium::Core::Template::System::int64_t Convert<C>::ToInt64(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase, const CorrespondingNumberFormatInfo& FormatInfo)
	{	// taken and adapted from: https://www.geeksforgeeks.org/write-your-own-atoi/
		Pointer ChangeableValue = (Pointer)Value;
		ConstPointer LastCharacter = &Value[Length];

		// sign
		System::int16_t Sign = 1;
		if (ChangeableValue[0] == CharacterTraits<C>::MinusCharacter || ChangeableValue[0] == CharacterTraits<C>::PlusCharacter)
		{
			Sign = 1 - 2 * (ChangeableValue[0] == CharacterTraits<C>::MinusCharacter);
			ChangeableValue++;
		}

		// ...
		System::int64_t AbsoluteResult = 0;
		while (ChangeableValue < LastCharacter)
		{
			if (CharacterTraits<C>::IsDigit(ChangeableValue[0]))
			{
				AbsoluteResult = FromBase * AbsoluteResult + static_cast<System::int64_t>(ChangeableValue[0] - CharacterTraits<C>::ZeroCharacter);
			}
			else if (CharacterTraits<C>::IsAsciiHexDigitLower(ChangeableValue[0]))
			{
				AbsoluteResult = FromBase * AbsoluteResult + (10_i64 + ChangeableValue[0] - CharacterTraits<C>::LowerACharacter);
			}
			else if (CharacterTraits<C>::IsAsciiHexDigitUpper(ChangeableValue[0]))
			{
				AbsoluteResult = FromBase * AbsoluteResult + (10_i64 + ChangeableValue[0] - CharacterTraits<C>::UpperACharacter);
			}
			else
			{
				break;
			}
			ChangeableValue++;
		}

		return AbsoluteResult * Sign;
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
	inline Elysium::Core::Template::System::int64_t Convert<C>::ToInt64(ConstPointer Value)
	{
		return ToInt64(Value, CharacterTraits<C>::GetLength(Value), 10, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline float Convert<C>::ToSingle(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase, const CorrespondingNumberFormatInfo& FormatInfo)
	{
		Pointer ChangeableValue = (Pointer)Value;
		ConstPointer LastCharacter = &Value[Length];

		// sign
		System::int16_t Sign = 1;
		if (ChangeableValue[0] == CharacterTraits<C>::MinusCharacter || ChangeableValue[0] == CharacterTraits<C>::PlusCharacter)
		{
			Sign = 1 - 2 * (ChangeableValue[0] == CharacterTraits<C>::MinusCharacter);
			ChangeableValue++;
		}

		// ...
		System::uint32_t AbsoluteResult = 0;
		while (ChangeableValue < LastCharacter && ChangeableValue[0] != static_cast<C>('.'))
		{
			if (CharacterTraits<C>::IsDigit(ChangeableValue[0]))
			{
				AbsoluteResult = FromBase * AbsoluteResult + static_cast<System::uint32_t>(ChangeableValue[0]) - CharacterTraits<C>::ZeroCharacter;
			}
			else if (CharacterTraits<C>::IsAsciiHexDigitLower(ChangeableValue[0]))
			{
				AbsoluteResult = FromBase * AbsoluteResult + (10_ui32 + ChangeableValue[0] - CharacterTraits<C>::LowerACharacter);
			}
			else if (CharacterTraits<C>::IsAsciiHexDigitUpper(ChangeableValue[0]))
			{
				AbsoluteResult = FromBase * AbsoluteResult + (10_ui32 + ChangeableValue[0] - CharacterTraits<C>::UpperACharacter);
			}
			else
			{
				break;
			}
			ChangeableValue++;
		}

		// skip .
		ChangeableValue++;
		
		// calculate the decimal value based on an integer to get a closer representation of the actual number
		System::uint32_t DecimalPointResult = 0;
		while (ChangeableValue < LastCharacter && ChangeableValue[0] != static_cast<C>('.'))
		{
			if (CharacterTraits<C>::IsDigit(ChangeableValue[0]))
			{
				DecimalPointResult = FromBase * DecimalPointResult + static_cast<System::uint32_t>(ChangeableValue[0]) - CharacterTraits<C>::ZeroCharacter;
			}
			else if (CharacterTraits<C>::IsAsciiHexDigitLower(ChangeableValue[0]))
			{
				DecimalPointResult = FromBase * DecimalPointResult + (10_ui32 + ChangeableValue[0] - CharacterTraits<C>::LowerACharacter);
			}
			else if (CharacterTraits<C>::IsAsciiHexDigitUpper(ChangeableValue[0]))
			{
				DecimalPointResult = FromBase * DecimalPointResult + (10_ui32 + ChangeableValue[0] - CharacterTraits<C>::UpperACharacter);
			}
			else
			{
				break;
			}
			ChangeableValue++;
		}

		return static_cast<float>((AbsoluteResult + static_cast<double>(DecimalPointResult) / Math::Power(10, Numeric::NumericTraits<System::uint32_t>::GetDigitCount(DecimalPointResult)))) * Sign;
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
	inline float Convert<C>::ToSingle(ConstPointer Value)
	{
		return ToSingle(Value, CharacterTraits<C>::GetLength(Value), 10, _InvariantInfo);
	}

	template<Concepts::Character C>
	inline double Convert<C>::ToDouble(ConstPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::uint8_t FromBase, const CorrespondingNumberFormatInfo& FormatInfo)
	{
		Pointer ChangeableValue = (Pointer)Value;
		ConstPointer LastCharacter = &Value[Length];

		// sign
		System::int16_t Sign = 1;
		if (ChangeableValue[0] == CharacterTraits<C>::MinusCharacter || ChangeableValue[0] == CharacterTraits<C>::PlusCharacter)
		{
			Sign = 1 - 2 * (ChangeableValue[0] == CharacterTraits<C>::MinusCharacter);
			ChangeableValue++;
		}

		// ...
		System::uint64_t AbsoluteResult = 0;
		while (ChangeableValue < LastCharacter && ChangeableValue[0] != static_cast<C>('.'))
		{
			if (CharacterTraits<C>::IsDigit(ChangeableValue[0]))
			{
				AbsoluteResult = FromBase * AbsoluteResult + static_cast<System::int64_t>(ChangeableValue[0]) - CharacterTraits<C>::ZeroCharacter;
			}
			else if (CharacterTraits<C>::IsAsciiHexDigitLower(ChangeableValue[0]))
			{
				AbsoluteResult = FromBase * AbsoluteResult + (10_ui64 + ChangeableValue[0] - CharacterTraits<C>::LowerACharacter);
			}
			else if (CharacterTraits<C>::IsAsciiHexDigitUpper(ChangeableValue[0]))
			{
				AbsoluteResult = FromBase * AbsoluteResult + (10_ui64 + ChangeableValue[0] - CharacterTraits<C>::UpperACharacter);
			}
			else
			{
				break;
			}
			ChangeableValue++;
		}

		// skip .
		ChangeableValue++;

		// calculate the decimal value based on an integer to get a closer representation of the actual number
		System::uint64_t DecimalPointResult = 0;
		while (ChangeableValue < LastCharacter && ChangeableValue[0] != static_cast<C>('.'))
		{
			if (CharacterTraits<C>::IsDigit(ChangeableValue[0]))
			{
				DecimalPointResult = FromBase * DecimalPointResult + static_cast<System::int64_t>(ChangeableValue[0]) - CharacterTraits<C>::ZeroCharacter;
			}
			else if (CharacterTraits<C>::IsAsciiHexDigitLower(ChangeableValue[0]))
			{
				DecimalPointResult = FromBase * DecimalPointResult + (10_ui64 + ChangeableValue[0] - CharacterTraits<C>::LowerACharacter);
			}
			else if (CharacterTraits<C>::IsAsciiHexDigitUpper(ChangeableValue[0]))
			{
				DecimalPointResult = FromBase * DecimalPointResult + (10_ui64 + ChangeableValue[0] - CharacterTraits<C>::UpperACharacter);
			}
			else
			{
				break;
			}
			ChangeableValue++;
		}

		return (AbsoluteResult + static_cast<double>(DecimalPointResult) / Math::Power(10,
			Numeric::NumericTraits<System::uint64_t>::GetDigitCount(DecimalPointResult))) * Sign;
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
	inline double Convert<C>::ToDouble(ConstPointer Value)
	{
		return ToDouble(Value, CharacterTraits<C>::GetLength(Value), 10, _InvariantInfo);
	}
}
#endif
