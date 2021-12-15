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

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "Primitives.hpp"
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

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CHARACTERCATEGORY
#include "CharacterCategory.hpp"
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
		using Value = C;
		using Pointer = C*;
		using ConstValue = const C;
		using ConstPointer = const C*;
		using ConstReference = const C&;

		using ConstInteger = const I;
	public:
		/// <summary>
		/// Returns the minimum number of bytes required to represent a single character.
		/// </summary>
		static constexpr const Elysium::Core::size MinimumByteLength = sizeof(C);

		/// <summary>
		/// Returns '\0' as specified character-type.
		/// </summary>
		static constexpr ConstValue NullTerminationCharacter = C();

		/// <summary>
		/// Returns '-' as specified character-type.
		/// </summary>
		static constexpr ConstValue MinusCharacter = static_cast<ConstValue>('-');

		/// <summary>
		/// Returns '+' as specified character-type.
		/// </summary>
		static constexpr ConstValue PlusCharacter = static_cast<ConstValue>('+');

		/// <summary>
		/// Returns whitespace as specified character-type.
		/// </summary>
		static constexpr ConstValue WhitespaceCharacter = static_cast<ConstValue>(' ');

		/// <summary>
		/// Returns the smallest possible value as specified character-type.
		/// </summary>
		static constexpr ConstValue MinimumValue = static_cast<ConstValue>(Elysium::Core::Template::Numeric::NumericLimits<I>::Minimum);

		/// <summary>
		/// Returns the largest possible value as specified character-type.
		/// </summary>
		static constexpr ConstValue MaximumValue = static_cast<ConstValue>(Elysium::Core::Template::Numeric::NumericLimits<I>::Maximum);
	public:
		/// <summary>
		/// Returns the number of characters in given string up until the first null-termination character.
		/// </summary>
		/// <param name="Start"></param>
		/// <returns></returns>
		static constexpr const Elysium::Core::size GetLength(ConstPointer Start) noexcept;

		/// <summary>
		/// Returns the number of bytes in given string up until the first null-termination character.
		/// </summary>
		/// <param name="Start"></param>
		/// <returns></returns>
		static constexpr const Elysium::Core::size GetSize(ConstPointer Start) noexcept;

		/// <summary>
		/// Returns whether given string is nullptr or not.
		/// </summary>
		/// <param name="Start"></param>
		/// <returns></returns>
		static constexpr const bool IsNull(ConstPointer Start) noexcept;

		/// <summary>
		/// Returns whether given string starts with null-termination character.
		/// </summary>
		/// <param name="Start"></param>
		/// <returns></returns>
		static constexpr const bool IsEmpty(ConstPointer Start) noexcept;

		/// <summary>
		/// Returns whether given string IsNull(...) or IsEmpty(...).
		/// </summary>
		/// <param name="Start"></param>
		/// <returns></returns>
		static constexpr const bool IsNullOrEmpty(ConstPointer Start) noexcept;

		/// <summary>
		/// Returns index of looked up value within given string and length if there's a match or -1 otherwise.
		/// </summary>
		/// <param name="Start"></param>
		/// <param name="Length"></param>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const Elysium::Core::size IndexOf(ConstPointer Start, const Elysium::Core::size Length, ConstValue Value) noexcept;

		/// <summary>
		/// Returns index of looked up sequence within given string and length if there's a match or -1 otherwise.
		/// </summary>
		/// <param name="Start"></param>
		/// <param name="Length"></param>
		/// <param name="Sequence"></param>
		/// <returns></returns>
		//static constexpr const Elysium::Core::size IndexOf(ConstPointer Start, const Elysium::Core::size Length, ConstPointer Sequence) noexcept;

		/// <summary>
		/// Returns 0 if both strings match each other, a negative value if ... or a positive value otherwise.
		/// </summary>
		/// <param name="Start"></param>
		/// <param name="OtherStart"></param>
		/// <param name="Length"></param>
		/// <returns></returns>
		static constexpr const Elysium::Core::int32_t Compare(ConstPointer Start, ConstPointer OtherStart, const Elysium::Core::size Length) noexcept;

		/// <summary>
		/// Returns a pointer to the first character matching given value found within given string or nullptr if there was no match.
		/// </summary>
		/// <param name="Start"></param>
		/// <param name="Length"></param>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr CharacterTraitsBase<C, I>::ConstPointer Find(ConstPointer Start, const Elysium::Core::size Length, ConstValue Value) noexcept;
	};

	template<Concepts::Character C, Concepts::Integer I>
	inline constexpr const Elysium::Core::size CharacterTraitsBase<C, I>::GetLength(ConstPointer Start) noexcept
	{
		if (Start == nullptr)
		{
			return 0;
		}

		Elysium::Core::size Length = 0;
		while (*Start != NullTerminationCharacter)
		{
			Length++;
			Start++;
		}

		return Length;
	}

	template<Concepts::Character C, Concepts::Integer I>
	inline constexpr const Elysium::Core::size CharacterTraitsBase<C, I>::GetSize(ConstPointer Start) noexcept
	{
		return GetLength(Start) * MinimumByteLength;
	}

	template<Concepts::Character C, Concepts::Integer I>
	inline constexpr const bool CharacterTraitsBase<C, I>::IsNull(ConstPointer Start) noexcept
	{
		return Start == nullptr;
	}

	template<Concepts::Character C, Concepts::Integer I>
	inline constexpr const bool CharacterTraitsBase<C, I>::IsEmpty(ConstPointer Start) noexcept
	{
		return Start == nullptr ? false : *Start == NullTerminationCharacter;
	}

	template<Concepts::Character C, Concepts::Integer I>
	inline constexpr const bool CharacterTraitsBase<C, I>::IsNullOrEmpty(ConstPointer Start) noexcept
	{
		return Start == nullptr ? true : *Start == NullTerminationCharacter;
	}

	template<Concepts::Character C, Concepts::Integer I>
	inline constexpr const Elysium::Core::size CharacterTraitsBase<C, I>::IndexOf(ConstPointer Start, const Elysium::Core::size Length, ConstValue Value) noexcept
	{
		if (Start == nullptr)
		{
			return static_cast<Elysium::Core::size>(-1);
		}

		ConstPointer CharPointer = __builtin_char_memchr(Start, Value, Length);
		return CharPointer == nullptr ? static_cast<Elysium::Core::size>(-1) : CharPointer - Start;
	}

	template<Concepts::Character C, Concepts::Integer I>
	inline constexpr const Elysium::Core::int32_t CharacterTraitsBase<C, I>::Compare(ConstPointer Start, ConstPointer OtherStart, const Elysium::Core::size Length) noexcept
	{
		return __builtin_memcmp(Start, OtherStart, Length);
	}

	template<Concepts::Character C, Concepts::Integer I>
	inline constexpr CharacterTraitsBase<C, I>::ConstPointer CharacterTraitsBase<C, I>::Find(ConstPointer Start, const Elysium::Core::size Length, ConstValue Value) noexcept
	{
		return __builtin_char_memchr(Start, Value, Length);
	}

	template <>
	inline constexpr CharacterTraitsBase<char8_t, unsigned char>::ConstPointer CharacterTraitsBase<char8_t, unsigned char>::Find(ConstPointer Start, const Elysium::Core::size Length, ConstValue Value) noexcept
	{
		Elysium::Core::size CopiedLength = Length;
		for (; 0 < CopiedLength; --CopiedLength, ++Start)
		{
			if (*Start == Value)
			{
				return Start;
			}
		}

		return nullptr;
	}

	/// <summary>
	/// 
	/// </summary>
	template <Concepts::Character C>
	struct CharacterTraits
	{ };

	/// <summary>
	/// 
	/// https://www.asciitable.com/
	/// </summary>
	template <>
	struct CharacterTraits<char> : public CharacterTraitsBase<char, signed char>
	{
	public:
		/// <summary>
		/// Returns the maximum number of bytes which can represent a single character.
		/// </summary>
		static constexpr const Elysium::Core::size MaximumByteLength = sizeof(char);
	public:
		//static constexpr const CharacterCategory GetCategory(ConstCharacter Value) noexcept;

		//static constexpr unsigned int ConvertToUtf32(ConstCharacter Value) noexcept;

		/// <summary>
		/// Indicates whether given value is categorized as a control-character.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsControl(ConstValue Value) noexcept;

		/// <summary>
		/// Indicates whether given value is categorized as a radix-10 digit-character.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsDigit(ConstValue Value) noexcept;

		/// <summary>
		/// Indicates whether given value is categorized as a letter-character.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsLetter(ConstValue Value) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsLetterOrDigit(ConstValue Value) noexcept;
		
		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsLower(ConstValue Value) noexcept;
		
		/// <summary>
		/// Indicates whether given value is categorized as a number-character.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsNumber(ConstValue Value) noexcept;
		
		//static constexpr const bool IsPunctuation(ConstValue Value) noexcept;
		
		//static constexpr const bool IsSeperator(ConstValue Value) noexcept;
		
		//static constexpr const bool IsSymbol(ConstValue Value) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsUpper(ConstValue Value) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsWhitespace(ConstValue Value) noexcept;

		//static constexpr C ToLower(ConstValue Value) noexcept;
		
		//static constexpr C ToLowerInvariant(ConstValue Value) noexcept;
		
		//static constexpr C ToUpper(ConstValue Value) noexcept;
		
		//static constexpr C ToUpperInvariant(ConstValue Value) noexcept;
	private:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsAscii(ConstValue Value) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsHighAscii(ConstValue Value) noexcept;
	};

	inline constexpr const bool CharacterTraits<char>::IsControl(CharacterTraits<char>::ConstValue Value) noexcept
	{
		return (Value >= 0x00 && Value < 0x20) || Value == 0x7F;
	}

	inline constexpr const bool CharacterTraits<char>::IsDigit(CharacterTraits<char>::ConstValue Value) noexcept
	{
		return (Value > 0x2F && Value < 0x3A);	// Radix-10 digits
	}

	inline constexpr const bool CharacterTraits<char>::IsLetter(CharacterTraits<char>::ConstValue Value) noexcept
	{
		return IsLower(Value) || IsUpper(Value);
	}

	inline constexpr const bool CharacterTraits<char>::IsLetterOrDigit(CharacterTraits<char>::ConstValue Value) noexcept
	{
		return IsDigit(Value) || IsLetter(Value);
	}

	inline constexpr const bool CharacterTraits<char>::IsLower(CharacterTraits<char>::ConstValue Value) noexcept
	{
		return (Value > 0x60 && Value < 0x7B);	// Latin small (lower case) letters
	}

	inline constexpr const bool CharacterTraits<char>::IsNumber(CharacterTraits<char>::ConstValue Value) noexcept
	{
		return (Value > 0x2F && Value < 0x3A);
	}

	inline constexpr const bool CharacterTraits<char>::IsUpper(CharacterTraits<char>::ConstValue Value) noexcept
	{
		return (Value > 0x40 && Value < 0x5B);	// Latin capital (upper case) letters
	}

	inline constexpr const bool CharacterTraits<char>::IsWhitespace(CharacterTraits<char>::ConstValue Value) noexcept
	{
		return Value == 0x20;
	}

	inline constexpr const bool CharacterTraits<char>::IsAscii(CharacterTraits<char>::ConstValue Value) noexcept
	{
		return (Value >= 0x00 && Value < 0x80);	// 0 - 127
	}

	inline constexpr const bool CharacterTraits<char>::IsHighAscii(CharacterTraits<char>::ConstValue Value) noexcept
	{
		return Value < 0x00;	// -128 - -1
	}

	/// <summary>
	/// 
	/// https://www.asciitable.com/
	/// </summary>
	template <>
	struct CharacterTraits<signed char> : public CharacterTraitsBase<signed char, signed char>
	{
	public:
		/// <summary>
		/// Returns the maximum number of bytes which can represent a single character.
		/// </summary>
		static constexpr const Elysium::Core::size MaximumByteLength = sizeof(signed char);
	public:
		/// <summary>
		/// Indicates whether given value is categorized as a control-character.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsControl(ConstValue Value) noexcept;

		/// <summary>
		/// Indicates whether given value is categorized as a radix-10 digit-character.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsDigit(ConstValue Value) noexcept;

		/// <summary>
		/// Indicates whether given value is categorized as a letter-character.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsLetter(ConstValue Value) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsLetterOrDigit(ConstValue Value) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsLower(ConstValue Value) noexcept;

		/// <summary>
		/// Indicates whether given value is categorized as a number-character.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsNumber(ConstValue Value) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsUpper(ConstValue Value) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsWhitespace(ConstValue Value) noexcept;
	private:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsAscii(ConstValue Value) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsHighAscii(ConstValue Value) noexcept;
	};

	inline constexpr const bool CharacterTraits<signed char>::IsControl(CharacterTraits<signed char>::ConstValue Value) noexcept
	{
		return (Value >= 0x00 && Value < 0x20) || Value == 0x7F;
	}

	inline constexpr const bool CharacterTraits<signed char>::IsDigit(CharacterTraits<signed char>::ConstValue Value) noexcept
	{
		return (Value > 0x2F && Value < 0x3A);	// Radix-10 digits
	}

	inline constexpr const bool CharacterTraits<signed char>::IsLetter(CharacterTraits<signed char>::ConstValue Value) noexcept
	{
		return IsLower(Value) || IsUpper(Value);
	}

	inline constexpr const bool CharacterTraits<signed char>::IsLetterOrDigit(CharacterTraits<signed char>::ConstValue Value) noexcept
	{
		return IsDigit(Value) || IsLetter(Value);
	}

	inline constexpr const bool CharacterTraits<signed char>::IsLower(CharacterTraits<signed char>::ConstValue Value) noexcept
	{
		return (Value > 0x60 && Value < 0x7B);	// Latin small (lower case) letters
	}

	inline constexpr const bool CharacterTraits<signed char>::IsNumber(CharacterTraits<signed char>::ConstValue Value) noexcept
	{
		return (Value > 0x2F && Value < 0x3A);
	}

	inline constexpr const bool CharacterTraits<signed char>::IsUpper(CharacterTraits<signed char>::ConstValue Value) noexcept
	{
		return (Value > 0x40 && Value < 0x5B);	// Latin capital (upper case) letters
	}

	inline constexpr const bool CharacterTraits<signed char>::IsWhitespace(CharacterTraits<signed char>::ConstValue Value) noexcept
	{
		return Value == 0x20;
	}

	inline constexpr const bool CharacterTraits<signed char>::IsAscii(CharacterTraits<signed char>::ConstValue Value) noexcept
	{
		return (Value >= 0x00 && Value < 0x80);	// 0 - 127
	}

	inline constexpr const bool CharacterTraits<signed char>::IsHighAscii(CharacterTraits<signed char>::ConstValue Value) noexcept
	{
		return Value < 0x00;	// -128 - -1
	}

	/// <summary>
	/// 
	/// https://www.asciitable.com/
	/// </summary>
	template <>
	struct CharacterTraits<unsigned char> : public CharacterTraitsBase<unsigned char, unsigned char>
	{
	public:
		/// <summary>
		/// Returns the maximum number of bytes which can represent a single character.
		/// </summary>
		static constexpr const Elysium::Core::size MaximumByteLength = sizeof(unsigned char);
	public:
		/// <summary>
		/// Indicates whether given value is categorized as a control-character.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsControl(ConstValue Value) noexcept;

		/// <summary>
		/// Indicates whether given value is categorized as a radix-10 digit-character.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsDigit(ConstValue Value) noexcept;

		/// <summary>
		/// Indicates whether given value is categorized as a letter-character.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsLetter(ConstValue Value) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsLetterOrDigit(ConstValue Value) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsLower(ConstValue Value) noexcept;

		/// <summary>
		/// Indicates whether given value is categorized as a number-character.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsNumber(ConstValue Value) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsUpper(ConstValue Value) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsWhitespace(ConstValue Value) noexcept;
	private:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsAscii(ConstValue Value) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsHighAscii(ConstValue Value) noexcept;
	};

	inline constexpr const bool CharacterTraits<unsigned char>::IsControl(CharacterTraits<unsigned char>::ConstValue Value) noexcept
	{
		return Value < 0x20 || (Value > 0x7E && Value < 0xA0);
	}

	inline constexpr const bool CharacterTraits<unsigned char>::IsDigit(CharacterTraits<unsigned char>::ConstValue Value) noexcept
	{
		return (Value > 0x2F && Value < 0x3A);	// Radix-10 digits
	}

	inline constexpr const bool CharacterTraits<unsigned char>::IsLetter(CharacterTraits<unsigned char>::ConstValue Value) noexcept
	{
		return IsLower(Value) || IsUpper(Value);
	}

	inline constexpr const bool CharacterTraits<unsigned char>::IsLetterOrDigit(CharacterTraits<unsigned char>::ConstValue Value) noexcept
	{
		return IsDigit(Value) || IsLetter(Value);
	}

	inline constexpr const bool CharacterTraits<unsigned char>::IsLower(CharacterTraits<unsigned char>::ConstValue Value) noexcept
	{
		return (Value > 0x60 && Value < 0x7B);	// Latin small (lower case) letters
	}

	inline constexpr const bool CharacterTraits<unsigned char>::IsNumber(CharacterTraits<unsigned char>::ConstValue Value) noexcept
	{
		return (Value > 0x2F && Value < 0x3A);
	}

	inline constexpr const bool CharacterTraits<unsigned char>::IsUpper(CharacterTraits<unsigned char>::ConstValue Value) noexcept
	{
		return (Value > 0x40 && Value < 0x5B);	// Latin capital (upper case) letters
	}

	inline constexpr const bool CharacterTraits<unsigned char>::IsWhitespace(CharacterTraits<unsigned char>::ConstValue Value) noexcept
	{
		return Value == 0x20;
	}

	inline constexpr const bool CharacterTraits<unsigned char>::IsAscii(CharacterTraits<unsigned char>::ConstValue Value) noexcept
	{
		return Value < 0x80;	// 0 - 127
	}

	inline constexpr const bool CharacterTraits<unsigned char>::IsHighAscii(CharacterTraits<unsigned char>::ConstValue Value) noexcept
	{
		return Value > 0x7F;	// 128 - 255
	}

	/// <summary>
	/// 
	/// </summary>
	template <>
	struct CharacterTraits<wchar_t> : public CharacterTraitsBase<wchar_t, unsigned short>
	{
	public:
		/// <summary>
		/// Returns the maximum number of bytes which can represent a single character.
		/// </summary>
		static constexpr const Elysium::Core::size MaximumByteLength = 4;
	public:
		/// <summary>
		/// Indicates whether given value is categorized as a control-character.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsControl(ConstValue Value) noexcept;
		
		//static constexpr const bool IsHighSurrogate(ConstValue Value) noexcept;

		//static constexpr const bool IsLowSurrogate(ConstValue Value) noexcept;
	};

	inline constexpr const bool CharacterTraits<wchar_t>::IsControl(CharacterTraits<wchar_t>::ConstValue Value) noexcept
	{	// https://www.fileformat.info/info/unicode/category/Cc/list.htm
		return Value < 0x20 || (Value > 0x7E && Value < 0xA0);
	}

	/// <summary>
	/// 
	/// </summary>
	template <>
	struct CharacterTraits<char8_t> : public CharacterTraitsBase<char8_t, unsigned char>
	{ 
	public:
		/// <summary>
		/// Returns the maximum number of bytes which can represent a single character.
		/// </summary>
		static constexpr const Elysium::Core::size MaximumByteLength = 4;
	public:
		/// <summary>
		/// Indicates whether given value is categorized as a control-character.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsControl(ConstValue Value) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsLeadByte(ConstValue Value) noexcept;
		
		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsTrailByte(ConstValue Value) noexcept;
	private:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsAscii(ConstValue Value) noexcept;
	};

	inline constexpr const bool CharacterTraits<char8_t>::IsControl(ConstValue Value) noexcept
	{	// https://www.fileformat.info/info/unicode/category/Cc/list.htm
		return Value < 0x20 || (Value > 0x7E && Value < 0xA0);
	}

	inline constexpr const bool CharacterTraits<char8_t>::IsLeadByte(CharacterTraits<char8_t>::ConstValue Value) noexcept
	{	// In UTF-8 a leading byte will always look like this: 0xxx xxxx, 110x xxxx, 1110 xxxx or 1111 0xxx
		/*
		if ((Value >> 7) == 0x00)
		{
			return true;
		}
		else if ((Value & 0xC0) == 0xC0)
		{
			return true;
		}
		else if ((Value & 0xE0) == 0xE0)
		{
			return true;
		}
		else if ((Value & 0xF0) == 0xF0)
		{
			return true;
		}

		return false;
		*/
		return (Value & 0x80) != 0x80;
	}

	inline constexpr const bool CharacterTraits<char8_t>::IsTrailByte(CharacterTraits<char8_t>::ConstValue Value) noexcept
	{	// In UTF-8 a trailing byte will always look like this: 10xx xxxx
		return (Value & 0x80) == 0x80;
	}

	inline constexpr const bool CharacterTraits<char8_t>::IsAscii(CharacterTraits<char8_t>::ConstValue Value) noexcept
	{
		return Value < 0x80;	// 0 - 127 (utf-8 is ascii compliant regarding these values)
	}

	/// <summary>
	/// 
	/// </summary>
	template <>
	struct CharacterTraits<char16_t> : public CharacterTraitsBase<char16_t, unsigned short>
	{
	public:
		/// <summary>
		/// Returns the maximum number of bytes which can represent a single character.
		/// </summary>
		static constexpr const Elysium::Core::size MaximumByteLength = 4;
		
		/// <summary>
		/// Indicates whether given value is categorized as a control-character.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsControl(ConstValue Value) noexcept;
		
		//static constexpr const bool IsHighSurrogate(ConstValue Value) noexcept;

		//static constexpr const bool IsLowSurrogate(ConstValue Value) noexcept;
	};

	inline constexpr const bool CharacterTraits<char16_t>::IsControl(CharacterTraits<char16_t>::ConstValue Value) noexcept
	{	// https://www.fileformat.info/info/unicode/category/Cc/list.htm
		return Value < 0x20 || (Value > 0x7E && Value < 0xA0);
	}

	/// <summary>
	/// 
	/// </summary>
	template <>
	struct CharacterTraits<char32_t> : public CharacterTraitsBase<char32_t, unsigned int>
	{
	public:
		/// <summary>
		/// Returns the maximum number of bytes which can represent a single character.
		/// </summary>
		static constexpr const Elysium::Core::size MaximumByteLength = sizeof(char32_t);
	public:
		/// <summary>
		/// Indicates whether given value is categorized as a control-character.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsControl(ConstValue Value) noexcept;

		/// <summary>
		/// Indicates whether given value is categorized as a radix-10 digit-character.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsDigit(ConstValue Value) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsLetter(ConstValue Value) noexcept;

		/// <summary>
		/// Indicates whether given value is categorized as a number-character.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsNumber(ConstValue Value) noexcept;
	private:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsAscii(ConstValue Value) noexcept;
	};

	inline constexpr const bool CharacterTraits<char32_t>::IsControl(CharacterTraits<char32_t>::ConstValue Value) noexcept
	{	// https://www.fileformat.info/info/unicode/category/Cc/list.htm
		return Value < 0x20 || (Value > 0x7E && Value < 0xA0);
	}

	inline constexpr const bool CharacterTraits<char32_t>::IsDigit(CharacterTraits<char32_t>::ConstValue Value) noexcept
	{
		return (Value > 0x2F && Value < 0x3A);	// Radix-10 digits
	}
	
	inline constexpr const bool CharacterTraits<char32_t>::IsLetter(CharacterTraits<char32_t>::ConstValue Value) noexcept
	{	// https://www.fileformat.info/info/unicode/category/LC/list.htm
		// https://www.fileformat.info/info/unicode/category/Ll/list.htm
		// https://www.fileformat.info/info/unicode/category/Lm/list.htm
		// https://www.fileformat.info/info/unicode/category/Lo/list.htm
		// https://www.fileformat.info/info/unicode/category/Lt/list.htm
		// https://www.fileformat.info/info/unicode/category/Lu/list.htm
		return false;
	}

	inline constexpr const bool CharacterTraits<char32_t>::IsNumber(CharacterTraits<char32_t>::ConstValue Value) noexcept
	{	// https://www.fileformat.info/info/unicode/category/Nd/list.htm
		return
			(Value > 0x2F && Value < 0x3A) ||			// Radix-10 digits
			(Value > 0x065F && Value < 0x066A) ||		// Arabic-Indic digits
			(Value > 0x06EF && Value < 0x06FA) ||		// Extended arabic-indic digits
			(Value > 0x07BF && Value < 0x07CA) ||		// Nko digits
			(Value > 0x0965 && Value < 0x0970) ||		// Devanagri digits
			(Value > 0x09E5 && Value < 0x09F0) || 		// Bengali digits
			(Value > 0x0A65 && Value < 0x0AF0) || 		// Gurmukhi and gurjarati digits
			(Value > 0x0B65 && Value < 0x0B70) || 		// Oriya digits
			(Value > 0x0BE5 && Value < 0x0BF0) || 		// Tamil digits
			(Value > 0x0C65 && Value < 0x0C70) || 		// Telugu digits
			(Value > 0x0CE5 && Value < 0x0CF0) || 		// Kannada digits
			(Value > 0x0D65 && Value < 0x0D70) || 		// Malayalam digits
			(Value > 0x0DE5 && Value < 0x0DF0) || 		// Sinhala lith digits
			(Value > 0x0E4F && Value < 0x0E5A) || 		// Thai digits
			(Value > 0x0ECF && Value < 0x0EDA) || 		// Lao digits
			(Value > 0x0F1F && Value < 0x0F2A) || 		// Tibetan digits
			(Value > 0x103F && Value < 0x104A) || 		// Myanmar digits
			(Value > 0x108F && Value < 0x109A) || 		// Myanmar shan digits
			(Value > 0x17DF && Value < 0x17E9) || 		// Khmer digits
			(Value > 0x180F && Value < 0x181A) || 		// Mongolian digits
			(Value > 0x1945 && Value < 0x1950) || 		// Limbu digits
			(Value > 0x19CF && Value < 0x19DA) || 		// New tai lue digits
			(Value > 0x1A7F && Value < 0x1A8A) || 		// Tai tham hora digits
			(Value > 0x1A8F && Value < 0x1A9A) || 		// Tai tham tham digits
			(Value > 0x1B4F && Value < 0x1B5A) || 		// Balinese digits
			(Value > 0x1BAF && Value < 0x1BBA) || 		// Sundanese digits
			(Value > 0x1C3F && Value < 0x1C4A) || 		// Lepcha digits
			(Value > 0x1C4F && Value < 0x1C5A) || 		// Ol chiki digits
			(Value > 0xA61F && Value < 0xA62A) || 		// Vai digits
			(Value > 0xA8CF && Value < 0xA8DA) || 		// Saurashtra digits
			(Value > 0xA8FF && Value < 0xA90A) || 		// Kayah li digits
			(Value > 0xA9CF && Value < 0xA9DA) || 		// Javanese digits
			(Value > 0xA9EF && Value < 0xA9FA) || 		// Myanmar tai laing digits
			(Value > 0xAA4F && Value < 0xAA5A) || 		// Cham digits
			(Value > 0xABEF && Value < 0xABFA) || 		// Meetei mayek digits
			(Value > 0xFF0F && Value < 0xFF1A) || 		// Fullwidth digits
			(Value > 0x01049F && Value < 0x0104AA) || 	// Osmanya digits
			(Value > 0x010D2F && Value < 0x010D3A) || 	// Hanifi rohingya digits
			(Value > 0x011065 && Value < 0x011070) || 	// Brahmi digits
			(Value > 0x0110EF && Value < 0x0110FA) ||	// Sora sompeng digits
			(Value > 0x011135 && Value < 0x011140) ||	// Charkma digits
			(Value > 0x0111CF && Value < 0x0111DA) ||	// Sharada digits
			(Value > 0x0112EF && Value < 0x0112FA) ||	// Khudawadi digits
			(Value > 0x01144F && Value < 0x01145A) ||	// Newa digits
			(Value > 0x0114CF && Value < 0x0114DA) ||	// Tirhuta digits
			(Value > 0x01164F && Value < 0x01165A) ||	// Modi digits
			(Value > 0x0116BF && Value < 0x0116CA) ||	// Takri digits
			(Value > 0x01172F && Value < 0x01173A) ||	// Ahom digits
			(Value > 0x0118DF && Value < 0x0118EA) ||	// Warang citi digits
			(Value > 0x01194F && Value < 0x01195A) ||	// Dives akuru digits
			(Value > 0x011C4F && Value < 0x011C5A) ||	// Bhaiksuki digits
			(Value > 0x011D4F && Value < 0x011D5A) ||	// Masaram gondi digits
			(Value > 0x011D9F && Value < 0x011DAA) ||	// Gunjala gondi digits
			(Value > 0x016A5F && Value < 0x016A6A) ||	// Mro digits
			(Value > 0x016ABF && Value < 0x016ACA) ||	// Tangsa digits
			(Value > 0x016B4F && Value < 0x016B5A) ||	// Pahawh hmong digits
			(Value > 0x01D7CD && Value < 0x01D800) ||	// Mathematical bold, mathematical double-struck, mathematical sans-serif, mathematical sans-serif bold and mathematical monospace digits
			(Value > 0x01E13F && Value < 0x01E14A) ||	// Nyiakeng puachue digits
			(Value > 0x01E2EF && Value < 0x01E2FA) ||	// Wancho digits
			(Value > 0x01E94F && Value < 0x01E95A) ||	// Adlam digits
			(Value > 0x01FBEF && Value < 0x1FBFA);		// Segmented digits
	}

	inline constexpr const bool CharacterTraits<char32_t>::IsAscii(CharacterTraits<char32_t>::ConstValue Value) noexcept
	{
		return Value < 0x80;	// 0 - 127 (utf-32 is ascii compliant regarding these values)
	}
}
#endif
