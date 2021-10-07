/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CHARACTERTRAITS
#define ELYSIUM_CORE_TEMPLATE_TEXT_CHARACTERTRAITS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_CHARACTER
#include "Character.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_INTEGER
#include "Integer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NUMERIC_NUMERICLIMITS
#include "NumericLimits.hpp"
#endif

namespace Elysium::Core::Template::Text
{
	/// <summary>
	/// 
	/// </summary>
	template <Concepts::Character C, Concepts::Integer I>
	struct CharacterTraitsBase
	{
	public:
		using ConstCharacter = const C;
		using ConstPointer = const C*;
		using ConstReference = const C&;

		using ConstInteger = const I;
	public:
		/// <summary>
		/// Returns the number of bytes required to represent a single character.
		/// </summary>
		static constexpr const size_t ByteLength = sizeof(C);

		/// <summary>
		/// Returns '\0' as specified character-type.
		/// </summary>
		static constexpr ConstCharacter NullTerminationCharacter = C();

		/// <summary>
		/// Returns the smallest value as specified character-type.
		/// </summary>
		static constexpr ConstCharacter MinValue = Elysium::Core::Template::Numeric::NumericLimits<I>::Minimum;

		/// <summary>
		/// Returns the largest value as specified character-type.
		/// </summary>
		static constexpr ConstCharacter MaxValue = Elysium::Core::Template::Numeric::NumericLimits<I>::Maximum;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsControl(ConstCharacter Value) noexcept;
	};

	template<Concepts::Character C, Concepts::Integer I>
	inline constexpr const bool CharacterTraitsBase<C, I>::IsControl(ConstCharacter Value) noexcept
	{	// https://www.fileformat.info/info/unicode/category/Cc/list.htm
		return Value < 0x20 || (Value > 0x7E && Value < 0xA0);
	}

	template <Concepts::Character C>
	struct CharacterTraits
	{ };

	template <>
	struct CharacterTraits<char> : public CharacterTraitsBase<char, unsigned char>
	{
		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr unsigned int ConvertToUtf32(ConstCharacter Value) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsDigit(ConstCharacter Value) noexcept;

		//static constexpr const bool IsLetter(ConstCharacter Value) noexcept;
		//static constexpr const bool IsLetterOrDigit(ConstCharacter Value) noexcept;
		//static constexpr const bool IsLower(ConstCharacter Value) noexcept;
		//static constexpr const bool IsNumber(ConstCharacter Value) noexcept;
		//static constexpr const bool IsPunctuation(ConstCharacter Value) noexcept;
		//static constexpr const bool IsSeperator(ConstCharacter Value) noexcept;
		//static constexpr const bool IsSymbol(ConstCharacter Value) noexcept;
		//static constexpr const bool IsUpper(ConstCharacter Value) noexcept;

		//static constexpr C ToLower(ConstCharacter Value) noexcept;
		//static constexpr C ToLowerInvariant(ConstCharacter Value) noexcept;
		//static constexpr C ToUpper(ConstCharacter Value) noexcept;
		//static constexpr C ToUpperInvariant(ConstCharacter Value) noexcept;
	};

	inline constexpr unsigned int CharacterTraits<char>::ConvertToUtf32(ConstCharacter Value) noexcept
	{
		return Value;
	}

	inline constexpr const bool CharacterTraits<char>::IsDigit(ConstCharacter Value) noexcept
	{	// https://www.fileformat.info/info/unicode/category/Nd/list.htm
		return (Value > 29 && Value < 40);
	}

	template <>
	struct CharacterTraits<signed char> : public CharacterTraitsBase<signed char, signed char>
	{
		//static constexpr unsigned int ConvertToUtf32(ConstCharacter Value) noexcept;
	};

	template <>
	struct CharacterTraits<unsigned char> : public CharacterTraitsBase<unsigned char, unsigned char>
	{
		//static constexpr unsigned int ConvertToUtf32(ConstCharacter Value) noexcept;
	};

	template <>
	struct CharacterTraits<wchar_t> : public CharacterTraitsBase<wchar_t, unsigned short>
	{
		//static constexpr unsigned int ConvertToUtf32(ConstCharacter HighSurrogate, ConstCharacter LowSurrogate);
		
		//static constexpr const bool IsHighSurrogate(ConstCharacter Value) noexcept;

		//static constexpr const bool IsLowSurrogate(ConstCharacter Value) noexcept;
	};

	template <>
	struct CharacterTraits<char8_t> : public CharacterTraitsBase<char8_t, unsigned char>
	{ 
	public:
		//static constexpr unsigned int ConvertToUtf32(ConstCharacter LeadByte, ConstCharacter TrailByte1, ConstCharacter TrailByte2, ConstCharacter TrailByte3);
		
		//static constexpr const bool IsLeadByte(ConstCharacter Value) noexcept;
		
		//static constexpr const bool IsTrailByte(ConstCharacter Value) noexcept;
	};

	template <>
	struct CharacterTraits<char16_t> : public CharacterTraitsBase<char16_t, unsigned short>
	{
	public:
		//static constexpr unsigned int ConvertToUtf32(ConstCharacter HighSurrogate, ConstCharacter LowSurrogate);
		// 
		//static constexpr const bool IsHighSurrogate(ConstCharacter Value) noexcept;

		//static constexpr const bool IsLowSurrogate(ConstCharacter Value) noexcept;
	};

	template <>
	struct CharacterTraits<char32_t> : public CharacterTraitsBase<char32_t, unsigned int>
	{
		//static constexpr unsigned int ConvertToUtf32(ConstCharacter Value) noexcept;
	};
}
#endif
