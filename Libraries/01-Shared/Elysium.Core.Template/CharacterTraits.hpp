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
		using ConstCharacter = const C;
		using ConstPointer = const C*;
		using ConstReference = const C&;

		using ConstInteger = const I;
	public:
		/// <summary>
		/// Returns the minimum number of bytes required to represent a single character.
		/// </summary>
		static constexpr const size_t MinimumByteLength = sizeof(C);

		/// <summary>
		/// Returns '\0' as specified character-type.
		/// </summary>
		static constexpr ConstCharacter NullTerminationCharacter = C();

		/// <summary>
		/// Returns the smallest possible value as specified character-type.
		/// </summary>
		static constexpr ConstCharacter MinimumValue = Elysium::Core::Template::Numeric::NumericLimits<I>::Minimum;

		/// <summary>
		/// Returns the largest possible value as specified character-type.
		/// </summary>
		static constexpr ConstCharacter MaximumValue = Elysium::Core::Template::Numeric::NumericLimits<I>::Maximum;
	};

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
		/// <summary>
		/// Returns the maximum number of bytes which can represent a single character.
		/// </summary>
		static constexpr const size_t MaximumByteLength = sizeof(char);

		//static constexpr const CharacterCategory GetCategory(ConstCharacter Value) noexcept;

		//static constexpr unsigned int ConvertToUtf32(ConstCharacter Value) noexcept;

		/// <summary>
		/// Indicates whether given value is categorized as a control-character.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsControl(ConstCharacter Value) noexcept;

		/// <summary>
		/// Indicates whether given value is categorized as a radix-10 digit-character.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsDigit(ConstCharacter Value) noexcept;

		/// <summary>
		/// Indicates whether given value is categorized as a letter-character.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsLetter(ConstCharacter Value) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsLetterOrDigit(ConstCharacter Value) noexcept;
		
		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsLower(ConstCharacter Value) noexcept;
		
		/// <summary>
		/// Indicates whether given value is categorized as a number-character.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsNumber(ConstCharacter Value) noexcept;
		
		//static constexpr const bool IsPunctuation(ConstCharacter Value) noexcept;
		
		//static constexpr const bool IsSeperator(ConstCharacter Value) noexcept;
		
		//static constexpr const bool IsSymbol(ConstCharacter Value) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsUpper(ConstCharacter Value) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsWhitespace(ConstCharacter Value) noexcept;

		//static constexpr C ToLower(ConstCharacter Value) noexcept;
		
		//static constexpr C ToLowerInvariant(ConstCharacter Value) noexcept;
		
		//static constexpr C ToUpper(ConstCharacter Value) noexcept;
		
		//static constexpr C ToUpperInvariant(ConstCharacter Value) noexcept;
	private:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsAscii(ConstCharacter Value) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsHighAscii(ConstCharacter Value) noexcept;
	};

	inline constexpr const bool CharacterTraits<char>::IsControl(ConstCharacter Value) noexcept
	{
		return (Value >= 0x00 && Value < 0x20) || Value == 0x7F;
	}

	inline constexpr const bool CharacterTraits<char>::IsDigit(ConstCharacter Value) noexcept
	{
		return (Value > 0x2F && Value < 0x3A);	// Radix-10 digits
	}

	inline constexpr const bool CharacterTraits<char>::IsLetter(ConstCharacter Value) noexcept
	{
		return IsLower(Value) || IsUpper(Value);
	}

	inline constexpr const bool CharacterTraits<char>::IsLetterOrDigit(ConstCharacter Value) noexcept
	{
		return IsDigit(Value) || IsLetter(Value);
	}

	inline constexpr const bool CharacterTraits<char>::IsLower(ConstCharacter Value) noexcept
	{
		return (Value > 0x60 && Value < 0x7B);	// Latin small (lower case) letters
	}

	inline constexpr const bool CharacterTraits<char>::IsNumber(ConstCharacter Value) noexcept
	{
		return (Value > 0x2F && Value < 0x3A);
	}

	inline constexpr const bool CharacterTraits<char>::IsUpper(ConstCharacter Value) noexcept
	{
		return (Value > 0x40 && Value < 0x5B);	// Latin capital (upper case) letters
	}

	inline constexpr const bool CharacterTraits<char>::IsWhitespace(ConstCharacter Value) noexcept
	{
		return Value == 0x20;
	}

	inline constexpr const bool CharacterTraits<char>::IsAscii(ConstCharacter Value) noexcept
	{
		return (Value >= 0x00 && Value < 0x80);	// 0 - 127
	}

	inline constexpr const bool CharacterTraits<char>::IsHighAscii(ConstCharacter Value) noexcept
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
		/// <summary>
		/// Returns the maximum number of bytes which can represent a single character.
		/// </summary>
		static constexpr const size_t MaximumByteLength = sizeof(signed char);

		/// <summary>
		/// Indicates whether given value is categorized as a control-character.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsControl(ConstCharacter Value) noexcept;

		/// <summary>
		/// Indicates whether given value is categorized as a radix-10 digit-character.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsDigit(ConstCharacter Value) noexcept;

		/// <summary>
		/// Indicates whether given value is categorized as a letter-character.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsLetter(ConstCharacter Value) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsLetterOrDigit(ConstCharacter Value) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsLower(ConstCharacter Value) noexcept;

		/// <summary>
		/// Indicates whether given value is categorized as a number-character.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsNumber(ConstCharacter Value) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsUpper(ConstCharacter Value) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsWhitespace(ConstCharacter Value) noexcept;
	private:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsAscii(ConstCharacter Value) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsHighAscii(ConstCharacter Value) noexcept;
	};

	inline constexpr const bool CharacterTraits<signed char>::IsControl(ConstCharacter Value) noexcept
	{
		return (Value >= 0x00 && Value < 0x20) || Value == 0x7F;
	}

	inline constexpr const bool CharacterTraits<signed char>::IsDigit(ConstCharacter Value) noexcept
	{
		return (Value > 0x2F && Value < 0x3A);	// Radix-10 digits
	}

	inline constexpr const bool CharacterTraits<signed char>::IsLetter(ConstCharacter Value) noexcept
	{
		return IsLower(Value) || IsUpper(Value);
	}

	inline constexpr const bool CharacterTraits<signed char>::IsLetterOrDigit(ConstCharacter Value) noexcept
	{
		return IsDigit(Value) || IsLetter(Value);
	}

	inline constexpr const bool CharacterTraits<signed char>::IsLower(ConstCharacter Value) noexcept
	{
		return (Value > 0x60 && Value < 0x7B);	// Latin small (lower case) letters
	}

	inline constexpr const bool CharacterTraits<signed char>::IsNumber(ConstCharacter Value) noexcept
	{
		return (Value > 0x2F && Value < 0x3A);
	}

	inline constexpr const bool CharacterTraits<signed char>::IsUpper(ConstCharacter Value) noexcept
	{
		return (Value > 0x40 && Value < 0x5B);	// Latin capital (upper case) letters
	}

	inline constexpr const bool CharacterTraits<signed char>::IsWhitespace(ConstCharacter Value) noexcept
	{
		return Value == 0x20;
	}

	inline constexpr const bool CharacterTraits<signed char>::IsAscii(ConstCharacter Value) noexcept
	{
		return (Value >= 0x00 && Value < 0x80);	// 0 - 127
	}

	inline constexpr const bool CharacterTraits<signed char>::IsHighAscii(ConstCharacter Value) noexcept
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
		/// <summary>
		/// Returns the maximum number of bytes which can represent a single character.
		/// </summary>
		static constexpr const size_t MaximumByteLength = sizeof(unsigned char);

		/// <summary>
		/// Indicates whether given value is categorized as a control-character.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsControl(ConstCharacter Value) noexcept;

		/// <summary>
		/// Indicates whether given value is categorized as a radix-10 digit-character.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsDigit(ConstCharacter Value) noexcept;

		/// <summary>
		/// Indicates whether given value is categorized as a letter-character.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsLetter(ConstCharacter Value) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsLetterOrDigit(ConstCharacter Value) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsLower(ConstCharacter Value) noexcept;

		/// <summary>
		/// Indicates whether given value is categorized as a number-character.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsNumber(ConstCharacter Value) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsUpper(ConstCharacter Value) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsWhitespace(ConstCharacter Value) noexcept;
	private:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsAscii(ConstCharacter Value) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsHighAscii(ConstCharacter Value) noexcept;
	};

	inline constexpr const bool CharacterTraits<unsigned char>::IsControl(ConstCharacter Value) noexcept
	{
		return Value < 0x20 || (Value > 0x7E && Value < 0xA0);
	}

	inline constexpr const bool CharacterTraits<unsigned char>::IsDigit(ConstCharacter Value) noexcept
	{
		return (Value > 0x2F && Value < 0x3A);	// Radix-10 digits
	}

	inline constexpr const bool CharacterTraits<unsigned char>::IsLetter(ConstCharacter Value) noexcept
	{
		return IsLower(Value) || IsUpper(Value);
	}

	inline constexpr const bool CharacterTraits<unsigned char>::IsLetterOrDigit(ConstCharacter Value) noexcept
	{
		return IsDigit(Value) || IsLetter(Value);
	}

	inline constexpr const bool CharacterTraits<unsigned char>::IsLower(ConstCharacter Value) noexcept
	{
		return (Value > 0x60 && Value < 0x7B);	// Latin small (lower case) letters
	}

	inline constexpr const bool CharacterTraits<unsigned char>::IsNumber(ConstCharacter Value) noexcept
	{
		return (Value > 0x2F && Value < 0x3A);
	}

	inline constexpr const bool CharacterTraits<unsigned char>::IsUpper(ConstCharacter Value) noexcept
	{
		return (Value > 0x40 && Value < 0x5B);	// Latin capital (upper case) letters
	}

	inline constexpr const bool CharacterTraits<unsigned char>::IsWhitespace(ConstCharacter Value) noexcept
	{
		return Value == 0x20;
	}

	inline constexpr const bool CharacterTraits<unsigned char>::IsAscii(ConstCharacter Value) noexcept
	{
		return Value < 0x80;	// 0 - 127
	}

	inline constexpr const bool CharacterTraits<unsigned char>::IsHighAscii(ConstCharacter Value) noexcept
	{
		return Value > 0x7F;	// 128 - 255
	}

	/// <summary>
	/// 
	/// </summary>
	template <>
	struct CharacterTraits<wchar_t> : public CharacterTraitsBase<wchar_t, unsigned short>
	{
		/// <summary>
		/// Returns the maximum number of bytes which can represent a single character.
		/// </summary>
		static constexpr const size_t MaximumByteLength = 4;

		/// <summary>
		/// Indicates whether given value is categorized as a control-character.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsControl(ConstCharacter Value) noexcept;
		
		//static constexpr const bool IsHighSurrogate(ConstCharacter Value) noexcept;

		//static constexpr const bool IsLowSurrogate(ConstCharacter Value) noexcept;
	};

	inline constexpr const bool CharacterTraits<wchar_t>::IsControl(ConstCharacter Value) noexcept
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
		static constexpr const size_t MaximumByteLength = 4;

		/// <summary>
		/// Indicates whether given value is categorized as a control-character.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsControl(ConstCharacter Value) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsLeadByte(ConstCharacter Value) noexcept;
		
		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsTrailByte(ConstCharacter Value) noexcept;
	private:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsAscii(ConstCharacter Value) noexcept;
	};

	inline constexpr const bool CharacterTraits<char8_t>::IsControl(ConstCharacter Value) noexcept
	{	// https://www.fileformat.info/info/unicode/category/Cc/list.htm
		return Value < 0x20 || (Value > 0x7E && Value < 0xA0);
	}

	inline constexpr const bool CharacterTraits<char8_t>::IsLeadByte(ConstCharacter Value) noexcept
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

	inline constexpr const bool CharacterTraits<char8_t>::IsTrailByte(ConstCharacter Value) noexcept
	{	// In UTF-8 a trailing byte will always look like this: 10xx xxxx
		return (Value & 0x80) == 0x80;
	}

	inline constexpr const bool CharacterTraits<char8_t>::IsAscii(ConstCharacter Value) noexcept
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
		static constexpr const size_t MaximumByteLength = 4;
		
		/// <summary>
		/// Indicates whether given value is categorized as a control-character.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsControl(ConstCharacter Value) noexcept;
		
		//static constexpr const bool IsHighSurrogate(ConstCharacter Value) noexcept;

		//static constexpr const bool IsLowSurrogate(ConstCharacter Value) noexcept;
	};

	inline constexpr const bool CharacterTraits<char16_t>::IsControl(ConstCharacter Value) noexcept
	{	// https://www.fileformat.info/info/unicode/category/Cc/list.htm
		return Value < 0x20 || (Value > 0x7E && Value < 0xA0);
	}

	/// <summary>
	/// 
	/// </summary>
	template <>
	struct CharacterTraits<char32_t> : public CharacterTraitsBase<char32_t, unsigned int>
	{
		/// <summary>
		/// Returns the maximum number of bytes which can represent a single character.
		/// </summary>
		static constexpr const size_t MaximumByteLength = sizeof(char32_t);

		/// <summary>
		/// Indicates whether given value is categorized as a control-character.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsControl(ConstCharacter Value) noexcept;

		/// <summary>
		/// Indicates whether given value is categorized as a radix-10 digit-character.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsDigit(ConstCharacter Value) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsLetter(ConstCharacter Value) noexcept;

		/// <summary>
		/// Indicates whether given value is categorized as a number-character.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsNumber(ConstCharacter Value) noexcept;
	private:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsAscii(ConstCharacter Value) noexcept;
	};

	inline constexpr const bool CharacterTraits<char32_t>::IsControl(ConstCharacter Value) noexcept
	{	// https://www.fileformat.info/info/unicode/category/Cc/list.htm
		return Value < 0x20 || (Value > 0x7E && Value < 0xA0);
	}

	inline constexpr const bool CharacterTraits<char32_t>::IsDigit(ConstCharacter Value) noexcept
	{
		return (Value > 0x2F && Value < 0x3A);	// Radix-10 digits
	}
	
	inline constexpr const bool CharacterTraits<char32_t>::IsLetter(ConstCharacter Value) noexcept
	{	// https://www.fileformat.info/info/unicode/category/LC/list.htm
		// https://www.fileformat.info/info/unicode/category/Ll/list.htm
		// https://www.fileformat.info/info/unicode/category/Lm/list.htm
		// https://www.fileformat.info/info/unicode/category/Lo/list.htm
		// https://www.fileformat.info/info/unicode/category/Lt/list.htm
		// https://www.fileformat.info/info/unicode/category/Lu/list.htm
		return false;
	}

	inline constexpr const bool CharacterTraits<char32_t>::IsNumber(ConstCharacter Value) noexcept
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

	inline constexpr const bool CharacterTraits<char32_t>::IsAscii(ConstCharacter Value) noexcept
	{
		return Value < 0x80;	// 0 - 127 (utf-32 is ascii compliant regarding these values)
	}
}
#endif
