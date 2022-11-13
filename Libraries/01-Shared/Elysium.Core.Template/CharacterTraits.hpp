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

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_CHARACTER
#include "Character.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_UNSIGNEDINTEGER
#include "UnsignedInteger.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NUMERIC_NUMERICTRAITS
#include "NumericTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_LITERALS
#include "Literals.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "OperatingSystem.hpp"
#endif

namespace Elysium::Core::Template::Text
{
	/// <summary>
	/// 
	/// </summary>
	template <Concepts::Character C, Concepts::UnsignedInteger I>
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
		static constexpr const System::size MinimumByteLength = sizeof(C);

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
		static constexpr ConstValue MinimumValue = static_cast<ConstValue>(Elysium::Core::Template::Numeric::NumericTraits<I>::Minimum);

		/// <summary>
		/// Returns the largest possible value as specified character-type.
		/// </summary>
		static constexpr ConstValue MaximumValue = static_cast<ConstValue>(Elysium::Core::Template::Numeric::NumericTraits<I>::Maximum);
	public:
		/// <summary>
		/// Returns the unicode code point representation.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const char32_t ConvertToUtf32(ConstPointer Value) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsValid(ConstPointer Value, System::size Length) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <param name="Length"></param>
		/// <returns></returns>
		static constexpr const bool IsValid(ConstPointer Value) noexcept;

		/// <summary>
		/// Determines whether a character is categorized as an ASCII character ([ U+0000..U+007F ]).
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsAscii(ConstValue Value) noexcept;

		/// <summary>
		/// Determines whether a character is categorized as a control character.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsControl(ConstValue Value) noexcept;

		/// <summary>
		/// Determines whether a character is categorized as a decimal digit. (radix-10 digits: 0 - 9)
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
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsHighAscii(ConstValue Value) noexcept;
		/*
		/// <summary>
		///
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
		///
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
		static constexpr const bool IsWhiteSpace(ConstValue Value) noexcept;
		*/
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="Destination"></param>
		/// <param name="Source"></param>
		/// <param name="Length"></param>
		static constexpr void Copy(Pointer Destination, ConstPointer Source, const Elysium::Core::Template::System::size Length);
	public:
		/// <summary>
		/// Returns 0 if both strings match each other, a negative value if ... or a positive value otherwise.
		/// </summary>
		/// <param name="Start"></param>
		/// <param name="OtherStart"></param>
		/// <param name="Length"></param>
		/// <returns></returns>
		static constexpr const System::int32_t Compare(ConstPointer Start, ConstPointer OtherStart, const System::size Length) noexcept;

		/// <summary>
		/// Returns a pointer to the first character matching given value found within given string or nullptr if there was no match.
		/// </summary>
		/// <param name="Start"></param>
		/// <param name="Length"></param>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr CharacterTraitsBase<C, I>::Pointer Find(ConstPointer Start, const System::size Length, ConstValue Value) noexcept;
	public:
		/// <summary>
		/// Returns the number of characters in given string up until the first null-termination character.
		/// </summary>
		/// <param name="Start"></param>
		/// <returns></returns>
		static constexpr const System::size GetLength(ConstPointer Start) noexcept;

		/// <summary>
		/// Returns the number of bytes in given string up until the first null-termination character.
		/// </summary>
		/// <param name="Start"></param>
		/// <returns></returns>
		static constexpr const System::size GetSize(ConstPointer Start) noexcept;
	public:
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
	public:
		/// <summary>
		/// Returns index of looked up value within given string and length if there's a match or -1 otherwise.
		/// </summary>
		/// <param name="Start"></param>
		/// <param name="Length"></param>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const System::size IndexOf(ConstPointer Start, const System::size Length, ConstValue Value) noexcept;

		/// <summary>
		/// Returns index of looked up sequence within given string and length if there's a match or -1 otherwise.
		/// </summary>
		/// <param name="Start"></param>
		/// <param name="Length"></param>
		/// <param name="Sequence"></param>
		/// <returns></returns>
		static constexpr const System::size IndexOf(ConstPointer Start, const System::size Length, ConstPointer Sequence) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Start"></param>
		/// <param name="Length"></param>
		/// <param name="Sequence"></param>
		/// <param name="SequenceLength"></param>
		/// <returns></returns>
		static constexpr const System::size IndexOfAny(ConstPointer Start, const System::size Length, ConstPointer Sequence,
			const System::size SequenceLength) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Start"></param>
		/// <param name="Length"></param>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const System::size LastIndexOf(ConstPointer Start, const System::size Length, ConstValue Value) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Start"></param>
		/// <param name="Length"></param>
		/// <param name="Sequence"></param>
		/// <returns></returns>
		static constexpr const System::size LastIndexOf(ConstPointer Start, const System::size Length, ConstPointer Sequence) noexcept;
	};

	/// <summary>
	/// 
	/// </summary>
	template <Concepts::Character C>
	struct CharacterTraits
	{ };

	/// <summary>
	/// https://en.wikipedia.org/wiki/ANSI_character_set
	/// https://en.wikipedia.org/wiki/ASCII
	/// https://en.wikipedia.org/wiki/Extended_ASCII
	/// https://en.wikipedia.org/wiki/ANSEL
	/// https://en.wikipedia.org/wiki/ISO/IEC_8859
	/// 
	/// https://www.asciitable.com/
	/// </summary>
	template <>
	struct CharacterTraits<char> : public CharacterTraitsBase<char, System::uint8_t>
	{
	public:
		/// <summary>
		/// Returns newline as specified character-type depending on the operating system.
		/// </summary>
		static constexpr ConstPointer NewLineCharacters =
#if defined ELYSIUM_CORE_OS_WINDOWS
			"\r\n";
#elif defined ELYSIUM_CORE_OS_ANDROID || ELYSIUM_CORE_OS_LINUX
			"\n";
#elif defined ELYSIUM_CORE_OS_MAC
			"\r";
#else
#error "unsupported os"
#endif

		/// <summary>
		/// Returns the maximum number of bytes which can represent a single character.
		/// </summary>
		static constexpr const System::size MaximumByteLength = sizeof(char);
	};

	/// <summary>
	/// https://en.wikipedia.org/wiki/UTF-8
	/// </summary>
	template <>
	struct CharacterTraits<char8_t> : public CharacterTraitsBase<char8_t, System::uint8_t>
	{
	public:
		/// <summary>
		/// Returns newline as specified character-type depending on the operating system.
		/// </summary>
		static constexpr ConstPointer NewLineCharacters =
#if defined ELYSIUM_CORE_OS_WINDOWS
			u8"\r\n";
#elif defined ELYSIUM_CORE_OS_ANDROID || ELYSIUM_CORE_OS_LINUX
			u8"\n";
#elif defined ELYSIUM_CORE_OS_MAC
			u8"\r";
#else
#error "unsupported os"
#endif

		/// <summary>
		/// Returns the maximum number of bytes which can represent a single character.
		/// </summary>
		static constexpr const System::size MaximumByteLength = 4;
	public:
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

		/// <summary>
		/// Returns the number of bytes used to represent a single character or -1 for a trail-byte which makes the evaluation impossible.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr System::uint8_t GetByteCount(ConstValue Value) noexcept;
	};

	/// <summary>
	/// https://en.wikipedia.org/wiki/UTF-16
	/// </summary>
	template <>
	struct CharacterTraits<char16_t> : public CharacterTraitsBase<char16_t, System::uint16_t>
	{
	private:
		/// <summary>
		/// https://learn.microsoft.com/en-us/windows/win32/api/winnls/nf-winnls-is_high_surrogate
		/// </summary>
		static constexpr const char16_t HighSurrogateLimits[2] = { 0xD800, 0xDBFF };

		/// <summary>
		/// https://learn.microsoft.com/en-us/windows/win32/api/winnls/nf-winnls-is_low_surrogate
		/// </summary>
		static constexpr const char16_t LowSurrogateLimits[2] = { 0xDC00, 0xDFFF };
	public:
		/// <summary>
		/// Returns newline as specified character-type depending on the operating system.
		/// </summary>
		static constexpr ConstPointer NewLineCharacters =
#if defined ELYSIUM_CORE_OS_WINDOWS
			u"\r\n";
#elif defined ELYSIUM_CORE_OS_ANDROID || ELYSIUM_CORE_OS_LINUX
			u"\n";
#elif defined ELYSIUM_CORE_OS_MAC
			u"\r";
#else
#error "unsupported os"
#endif

		/// <summary>
		/// Returns the maximum number of bytes which can represent a single character.
		/// </summary>
		static constexpr const System::size MaximumByteLength = 4;
	public:
		/// <summary>
		/// 
		/// </summary>
		static constexpr const bool IsHighSurrogate(ConstValue Value) noexcept;

		/// <summary>
		/// 
		/// </summary>
		static constexpr const bool IsLowSurrogate(ConstValue Value) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="First"></param>
		/// <param name="Second"></param>
		/// <returns></returns>
		static constexpr const bool IsSurrogatePair(ConstValue First, ConstValue Second) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr System::uint8_t GetByteCount(ConstValue Value) noexcept;
	};

	/// <summary>
	/// https://en.wikipedia.org/wiki/UTF-32
	/// </summary>
	template <>
	struct CharacterTraits<char32_t> : public CharacterTraitsBase<char32_t, System::uint32_t>
	{
	public:
		/// <summary>
		/// Returns newline as specified character-type depending on the operating system.
		/// </summary>
		static constexpr ConstPointer NewLineCharacters =
#if defined ELYSIUM_CORE_OS_WINDOWS
			U"\r\n";
#elif defined ELYSIUM_CORE_OS_ANDROID || ELYSIUM_CORE_OS_LINUX
			U"\n";
#elif defined ELYSIUM_CORE_OS_MAC
			U"\r";
#else
#error "unsupported os"
#endif

		/// <summary>
		/// Returns the maximum number of bytes which can represent a single character.
		/// </summary>
		static constexpr const System::size MaximumByteLength = sizeof(System::uint32_t);
	};
	
	/// <summary>
	/// https://en.wikipedia.org/wiki/UTF-16
	/// </summary>
	template <>
	struct CharacterTraits<wchar_t> : public CharacterTraitsBase<wchar_t, System::uint16_t>
	{
	private:
		/// <summary>
		/// https://learn.microsoft.com/en-us/windows/win32/api/winnls/nf-winnls-is_high_surrogate
		/// </summary>
		static constexpr const wchar_t HighSurrogateLimits[2] = { 0xD800, 0xDBFF };

		/// <summary>
		/// https://learn.microsoft.com/en-us/windows/win32/api/winnls/nf-winnls-is_low_surrogate
		/// </summary>
		static constexpr const wchar_t LowSurrogateLimits[2] = { 0xDC00, 0xDFFF };
	public:
		/// <summary>
		/// Returns newline as specified character-type depending on the operating system.
		/// </summary>
		static constexpr ConstPointer NewLineCharacters =
#if defined ELYSIUM_CORE_OS_WINDOWS
			L"\r\n";
#elif defined ELYSIUM_CORE_OS_ANDROID || ELYSIUM_CORE_OS_LINUX
			L"\n";
#elif defined ELYSIUM_CORE_OS_MAC
			L"\r";
#else
#error "unsupported os"
#endif

		/// <summary>
		/// Returns the maximum number of bytes which can represent a single character.
		/// </summary>
		static constexpr const System::size MaximumByteLength = 4;
	public:
		/// <summary>
		/// 
		/// </summary>
		static constexpr const bool IsHighSurrogate(ConstValue Value) noexcept;

		/// <summary>
		/// 
		/// </summary>
		static constexpr const bool IsLowSurrogate(ConstValue Value) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="First"></param>
		/// <param name="Second"></param>
		/// <returns></returns>
		static constexpr const bool IsSurrogatePair(ConstValue First, ConstValue Second) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr System::uint8_t GetByteCount(ConstValue Value) noexcept;
	};

	template<>
	inline constexpr const char32_t CharacterTraitsBase<char, System::uint8_t>::ConvertToUtf32(ConstPointer Value) noexcept
	{
		return char32_t(Value[0]);
	}

	template<>
	inline constexpr const char32_t CharacterTraitsBase<char8_t, System::uint8_t>::ConvertToUtf32(ConstPointer Value) noexcept
	{
		switch (CharacterTraits<char8_t>::GetByteCount(*Value))
		{
		case 1:		// 0xxx xxxx										->	0xxx xxxx
			return static_cast<char32_t>(Value[0]);
		case 2:		// 110y yyyy	10xx xxxx							->	0000 0yyy	yyxx xxxx
			return char32_t(((Value[0] & 0x1F) << 6) | (Value[1] & 0x3F));
		case 3:		// 1110 zzzz	10yy yyyy	10xx xxxx				->	zzzz yyyy	yyxx xxxx
			return char32_t(((Value[0] & 0x0F) << 12) | ((Value[1] & 0x3F) << 6) | (Value[3] & 0x3F));
		case 4:		// 1111 0aaa	10zz zzzz	10yy yyyyy	10xx xxxx	->	000a aazz	zzzz yyyy	yyxx xxxx
			return char32_t(((Value[0] & 0x07) << 18) | ((Value[1] & 0x3F) << 12) | ((Value[2] & 0x3F) << 6) | (Value[3] & 0x3F));
		default:	// 10xx xxxx (trail byte. determination not possible)
			return static_cast<char32_t>(-1);
		}
	}

	template<>
	inline constexpr const char32_t CharacterTraitsBase<char16_t, System::uint16_t>::ConvertToUtf32(ConstPointer Value) noexcept
	{
		if (CharacterTraits<char16_t>::IsHighSurrogate(Value[0]))
		{
			return char32_t((Value[0] << 10) + Value[1] - 0x35FDC00);
		}
		/*
		* As a low surrogate cannot be converted to UTF-32 on it's own, given value is an error on the user's part.
		* To reduce the number of function calls I do therefore not handle that case.
		else if (CharacterTraits<char16_t>::IsLowSurrogate(Value[0]))
		{
			return -1_ui32;
		}
		*/
		else
		{
			return static_cast<char32_t>(Value[0]);
		}
	}

	template<>
	inline constexpr const char32_t CharacterTraitsBase<char32_t, System::uint32_t>::ConvertToUtf32(ConstPointer Value) noexcept
	{
		return *Value;
	}

	template<>
	inline constexpr const char32_t CharacterTraitsBase<wchar_t, System::uint16_t>::ConvertToUtf32(ConstPointer Value) noexcept
	{
		if (CharacterTraits<wchar_t>::IsHighSurrogate(Value[0]))
		{
			return char32_t((Value[0] << 10) + Value[1] - 0x35FDC00);
		}
		/*
		* As a low surrogate cannot be converted to UTF-32 on it's own, given value is an error on the user's part.
		* To reduce the number of function calls I do therefore not handle that case.
		else if (CharacterTraits<wchar_t>::IsLowSurrogate(Value[0]))
		{
			return -1_ui32;
		}
		*/
		else
		{
			return static_cast<char32_t>(Value[0]);
		}
	}

	template<Concepts::Character C, Concepts::UnsignedInteger I>
	inline constexpr const char32_t CharacterTraitsBase<C, I>::ConvertToUtf32(ConstPointer Value) noexcept
	{
		return -1_ui32;
	}

	template<>
	inline constexpr const bool CharacterTraitsBase<char, System::uint8_t>::IsValid(ConstPointer Value, const System::size Length) noexcept
	{
		return true;
	}

	template<>
	inline constexpr const bool CharacterTraitsBase<char8_t, System::uint8_t>::IsValid(ConstPointer Value, System::size Length) noexcept
	{
		System::size ByteCount;
		for (System::size i = 0; i < Length; i++)
		{
			ByteCount = CharacterTraits<char8_t>::GetByteCount(Value[i]);
			if (ByteCount > Length)
			{
				return false;
			}

			if (!CharacterTraits<char8_t>::IsLeadByte(Value[i]))
			{
				return false;
			}

			for (System::size j = 0; j < ByteCount - 1; j++)
			{
				if (!CharacterTraits<char8_t>::IsTrailByte(Value[i++]))
				{
					return false;
				}
			}
		}

		return true;
	}

	template<>
	inline constexpr const bool CharacterTraitsBase<char16_t, System::uint16_t>::IsValid(ConstPointer Value, System::size Length) noexcept
	{
		return false;
	}

	template<>
	inline constexpr const bool CharacterTraitsBase<char32_t, System::uint32_t>::IsValid(ConstPointer Value, System::size Length) noexcept
	{
		return false;
	}

	template<>
	inline constexpr const bool CharacterTraitsBase<wchar_t, System::uint16_t>::IsValid(ConstPointer Value, System::size Length) noexcept
	{
		return false;
	}

	template<Concepts::Character C, Concepts::UnsignedInteger I>
	inline constexpr const bool CharacterTraitsBase<C, I>::IsValid(ConstPointer Value, System::size Length) noexcept
	{
		return false;
	}

	template<Concepts::Character C, Concepts::UnsignedInteger I>
	inline constexpr const bool CharacterTraitsBase<C, I>::IsValid(ConstPointer Value) noexcept
	{
		if (Value == nullptr)
		{
			return false;
		}

		return CharacterTraitsBase<C, I>::IsValid(Value, CharacterTraitsBase<C, I>::GetLength(Value));
	}

	template<Concepts::Character C, Concepts::UnsignedInteger I>
	inline constexpr const bool CharacterTraitsBase<C, I>::IsAscii(ConstValue Value) noexcept
	{
		return static_cast<ConstInteger>(Value) < 0x80;
	}

	template<>
	inline constexpr const bool CharacterTraitsBase<char, System::uint8_t>::IsControl(ConstValue Value) noexcept
	{
		return static_cast<ConstInteger>(Value) < 0x20 || static_cast<ConstInteger>(Value) == 0x7F;
	}

	template<Concepts::Character C, Concepts::UnsignedInteger I>
	inline constexpr const bool CharacterTraitsBase<C, I>::IsControl(ConstValue Value) noexcept
	{	// https://www.fileformat.info/info/unicode/category/Cc/list.htm
		return static_cast<ConstInteger>(Value) < 0x20 || (static_cast<ConstInteger>(Value) > 0x7E && static_cast<ConstInteger>(Value) < 0xA0);
	}

	template<Concepts::Character C, Concepts::UnsignedInteger I>
	inline constexpr const bool CharacterTraitsBase<C, I>::IsDigit(ConstValue Value) noexcept
	{	// https://www.fileformat.info/info/unicode/category/Nd/list.htm
		return static_cast<ConstInteger>(Value) > 0x2F && static_cast<ConstInteger>(Value) < 0x3A;
	}

	template<Concepts::Character C, Concepts::UnsignedInteger I>
	inline constexpr const bool CharacterTraitsBase<C, I>::IsLetter(ConstValue Value) noexcept
	{	// ToDo:
		return false;
	}

	template<>
	inline constexpr const bool CharacterTraitsBase<char, System::uint8_t>::IsHighAscii(ConstValue Value) noexcept
	{
		return Value >> 7_ui8 != 0x00_ui8;	// 1xxx xxxx (128 - 255)
	}

	template<>
	inline constexpr const bool CharacterTraitsBase<char8_t, System::uint8_t>::IsHighAscii(ConstValue Value) noexcept
	{
		return Value >> 7_ui8 != 0x00_ui8;	// 1xxx xxxx (128 - 255)
		// while a trail byte looks like 10xx xxxx, this just'd be an error on the user's part
	}

	template<Concepts::Character C, Concepts::UnsignedInteger I>
	inline constexpr const bool CharacterTraitsBase<C, I>::IsHighAscii(ConstValue Value) noexcept
	{
		return Value > 127 && Value < 256;
	}

	template<Concepts::Character C, Concepts::UnsignedInteger I>
	inline constexpr void CharacterTraitsBase<C, I>::Copy(Pointer Destination, ConstPointer Source, const Elysium::Core::Template::System::size Length)
	{
		memcpy(Destination, Source, Length * CharacterTraits<C>::MinimumByteLength);
	}
	
	template<Concepts::Character C, Concepts::UnsignedInteger I>
	inline constexpr const Elysium::Core::Template::System::int32_t CharacterTraitsBase<C, I>::Compare(ConstPointer Start, ConstPointer OtherStart, const Elysium::Core::Template::System::size Length) noexcept
	{
		return __builtin_memcmp(Start, OtherStart, Length);
	}

	template <>
	inline constexpr CharacterTraitsBase<char8_t, System::uint8_t>::Pointer CharacterTraitsBase<char8_t, System::uint8_t>::Find(ConstPointer Start, const Elysium::Core::Template::System::size Length, ConstValue Value) noexcept
	{
		ConstPointer LastCharacter = &Start[Length];
		while (Start < LastCharacter)
		{
			if (*Start == Value)
			{
				return (Pointer)Start;
			}
			Start++;
		}

		return nullptr;
	}

	template <>
	inline constexpr CharacterTraitsBase<char16_t, System::uint16_t>::Pointer CharacterTraitsBase<char16_t, System::uint16_t>::Find(ConstPointer Start, const Elysium::Core::Template::System::size Length, ConstValue Value) noexcept
	{
		ConstPointer LastCharacter = &Start[Length];
		while (Start < LastCharacter)
		{
			if (*Start == Value)
			{
				return (Pointer)Start;
			}
			Start++;
		}

		return nullptr;
	}

	template <>
	inline constexpr CharacterTraitsBase<char32_t, System::uint32_t>::Pointer CharacterTraitsBase<char32_t, System::uint32_t>::Find(ConstPointer Start, const Elysium::Core::Template::System::size Length, ConstValue Value) noexcept
	{
		ConstPointer LastCharacter = &Start[Length];
		while (Start < LastCharacter)
		{
			if (*Start == Value)
			{
				return (Pointer)Start;
			}
			Start++;
		}

		return nullptr;
	}

	template <>
	inline constexpr CharacterTraitsBase<wchar_t, System::uint16_t>::Pointer CharacterTraitsBase<wchar_t, System::uint16_t>::Find(ConstPointer Start, const Elysium::Core::Template::System::size Length, ConstValue Value) noexcept
	{
		ConstPointer LastCharacter = &Start[Length];
		while (Start < LastCharacter)
		{
			if (*Start == Value)
			{
				return (Pointer)Start;
			}
			Start++;
		}

		return nullptr;
	}

	template<Concepts::Character C, Concepts::UnsignedInteger I>
	inline constexpr CharacterTraitsBase<C, I>::Pointer CharacterTraitsBase<C, I>::Find(ConstPointer Start, const Elysium::Core::Template::System::size Length, ConstValue Value) noexcept
	{
		return __builtin_char_memchr(Start, Value, Length);
	}
	
	template<Concepts::Character C, Concepts::UnsignedInteger I>
	inline constexpr const Elysium::Core::Template::System::size CharacterTraitsBase<C, I>::GetLength(ConstPointer Start) noexcept
	{
		ConstPointer FirstCharacter = Start;
		while (*Start != NullTerminationCharacter)
		{
			Start++;
		}

		return Start - FirstCharacter;
	}

	template<Concepts::Character C, Concepts::UnsignedInteger I>
	inline constexpr const Elysium::Core::Template::System::size CharacterTraitsBase<C, I>::GetSize(ConstPointer Start) noexcept
	{
		return GetLength(Start) * MinimumByteLength;
	}

	template<Concepts::Character C, Concepts::UnsignedInteger I>
	inline constexpr const bool CharacterTraitsBase<C, I>::IsNull(ConstPointer Start) noexcept
	{
		return Start == nullptr;
	}

	template<Concepts::Character C, Concepts::UnsignedInteger I>
	inline constexpr const bool CharacterTraitsBase<C, I>::IsEmpty(ConstPointer Start) noexcept
	{
		return Start == nullptr ? false : *Start == NullTerminationCharacter;
	}

	template<Concepts::Character C, Concepts::UnsignedInteger I>
	inline constexpr const bool CharacterTraitsBase<C, I>::IsNullOrEmpty(ConstPointer Start) noexcept
	{
		return Start == nullptr ? true : *Start == NullTerminationCharacter;
	}

	template<Concepts::Character C, Concepts::UnsignedInteger I>
	inline constexpr const Elysium::Core::Template::System::size CharacterTraitsBase<C, I>::IndexOf(ConstPointer Start, const Elysium::Core::Template::System::size Length, ConstValue Value) noexcept
	{
		if (Start == nullptr || Length == 0)
		{
			return static_cast<Elysium::Core::Template::System::size>(-1);
		}

		ConstPointer CharacterPointer = CharacterTraitsBase<C, I>::Find(Start, Length, Value);
		return CharacterPointer == nullptr ? static_cast<Elysium::Core::Template::System::size>(-1) : CharacterPointer - Start;
	}

	template<Concepts::Character C, Concepts::UnsignedInteger I>
	inline constexpr const Elysium::Core::Template::System::size CharacterTraitsBase<C, I>::IndexOf(ConstPointer Start, const Elysium::Core::Template::System::size Length, ConstPointer Sequence) noexcept
	{
		if (Start == nullptr || Length == 0 || Sequence == nullptr)
		{
			return static_cast<Elysium::Core::Template::System::size>(-1);
		}

		ConstPointer LastCharacter = &Start[Length];
		Pointer CurrentCharacter = (Pointer)Start;

		ConstPointer LastSequenceCharacter = &Sequence[CharacterTraitsBase<C, I>::GetLength(Sequence)];
		Pointer CurrentSequenceCharacter = (Pointer)Sequence;

		Pointer FirstMatchingCharacter = CurrentCharacter;
		
		while (CurrentCharacter < LastCharacter)
		{
			// lookup the first sequence-character specifically outside the inner loop. if it wasn't found, there is no need to look any further.
			CurrentCharacter = CharacterTraitsBase<C, I>::Find(CurrentCharacter, LastCharacter - CurrentCharacter, CurrentSequenceCharacter[0]);
			if (CurrentCharacter == nullptr)
			{
				return static_cast<Elysium::Core::Template::System::size>(-1);
			}
			FirstMatchingCharacter = CurrentCharacter;

			// another early cancel if the rest of the string isn't long enough to hold all sequence-characters
			if (LastCharacter - CurrentCharacter < LastSequenceCharacter - CurrentSequenceCharacter)
			{
				return static_cast<Elysium::Core::Template::System::size>(-1);
			}

			// compare the following characters
			while (CurrentCharacter < LastCharacter)
			{
				++CurrentCharacter;
				++CurrentSequenceCharacter;
				if (CurrentSequenceCharacter == LastSequenceCharacter)
				{
					break;
				}

				if (*CurrentCharacter != *CurrentSequenceCharacter)
				{
					CurrentSequenceCharacter = (Pointer)Sequence;
					break;
				}
			}

			if (CurrentSequenceCharacter == LastSequenceCharacter)
			{
				return FirstMatchingCharacter - Start;
			}
		}

		return static_cast<Elysium::Core::Template::System::size>(-1);
	}

	template<Concepts::Character C, Concepts::UnsignedInteger I>
	inline constexpr const System::size CharacterTraitsBase<C, I>::IndexOfAny(ConstPointer Start, const Elysium::Core::Template::System::size Length, ConstPointer Sequence, const Elysium::Core::Template::System::size SequenceLength) noexcept
	{
		if (Start == nullptr || Length == 0 || Sequence == nullptr || SequenceLength == 0)
		{
			return static_cast<Elysium::Core::Template::System::size>(-1);
		}

		ConstPointer LastCharacter = &Start[Length];
		Pointer CurrentCharacter = (Pointer)Start;

		ConstPointer LastSequenceCharacter = &Sequence[SequenceLength];
		Pointer CurrentSequenceCharacter = (Pointer)Sequence;

		while (CurrentCharacter < LastCharacter) 
		{
			while (CurrentSequenceCharacter < LastSequenceCharacter)
			{
				if (*CurrentCharacter == *CurrentSequenceCharacter)
				{
					return LastCharacter - CurrentCharacter;
				}
				++CurrentSequenceCharacter;
			}
			++CurrentCharacter;
			CurrentSequenceCharacter = (Pointer)Sequence;
		}

		return static_cast<Elysium::Core::Template::System::size>(-1);
	}

	template<Concepts::Character C, Concepts::UnsignedInteger I>
	inline constexpr const Elysium::Core::Template::System::size CharacterTraitsBase<C, I>::LastIndexOf(ConstPointer Start, const Elysium::Core::Template::System::size Length, ConstValue Value) noexcept
	{
		Pointer CharacterPointer = nullptr;
		for (Elysium::Core::Template::System::size i = Length; i > 0; i--)
		{
			if (Start[i - 1] == Value)
			{
				CharacterPointer = (Pointer)&Start[i - 1];
				break;
			}
		}
		return CharacterPointer == nullptr ? static_cast<Elysium::Core::Template::System::size>(-1) : CharacterPointer - Start;
	}

	template<Concepts::Character C, Concepts::UnsignedInteger I>
	inline constexpr const Elysium::Core::Template::System::size CharacterTraitsBase<C, I>::LastIndexOf(ConstPointer Start, const Elysium::Core::Template::System::size Length, ConstPointer Sequence) noexcept
	{
		return -1;
	}
	
	inline constexpr const bool CharacterTraits<char8_t>::IsLeadByte(CharacterTraits<char8_t>::ConstValue Value) noexcept
	{	// In UTF-8 a leading byte will always look like this: 0xxx xxxx, 110x xxxx, 1110 xxxx or 1111 0xxx
		// instead of checking all these conditions I can simply make sure it's not a trailing byte
		//return (Value & CharacterTraits<char8_t>::TrailByteBitMask) != CharacterTraits<char8_t>::TrailByteBitMask;
		return Value >> 6_ui8 != 0x02_ui8;
	}

	inline constexpr const bool CharacterTraits<char8_t>::IsTrailByte(CharacterTraits<char8_t>::ConstValue Value) noexcept
	{	// In UTF-8 a trailing byte will always look like this: 10xx xxxx
		//return (Value & CharacterTraits<char8_t>::TrailByteBitMask) == CharacterTraits<char8_t>::TrailByteBitMask;
		return Value >> 6_ui8 == 0x02_ui8;
	}

	inline constexpr System::uint8_t CharacterTraits<char8_t>::GetByteCount(ConstValue Value) noexcept
	{
		if (Value >> 6_ui8 == 0x02_ui8)
		{	// 10xx xxxx (trail byte, ergo no way to tell how many bytes are used for a character)
			return -1_ui8;
		}
		else if (Value >> 7_ui8 == 0x00_ui8)
		{	// 0xxx xxxx
			return 1_ui8;
		}
		else if (Value >> 5_ui8 == 0x06_ui8)
		{	// 110y yyyy
			return 2_ui8;
		}
		else if (Value >> 4_ui8 == 0x0E_ui8)
		{	// 1110 zzzz
			return 3_ui8;
		}
		else if (Value >> 3_ui8 == 0x1E_ui8)
		{	// 1111 0aaa
			return 4_ui8;
		}
	}

	inline constexpr const bool CharacterTraits<char16_t>::IsHighSurrogate(ConstValue Value) noexcept
	{
		return Value >= CharacterTraits<char16_t>::HighSurrogateLimits[0] && Value <= CharacterTraits<char16_t>::HighSurrogateLimits[1];
	}

	inline constexpr const bool CharacterTraits<char16_t>::IsLowSurrogate(ConstValue Value) noexcept
	{
		return Value >= CharacterTraits<char16_t>::LowSurrogateLimits[0] && Value <= CharacterTraits<char16_t>::LowSurrogateLimits[1];
	}

	inline constexpr const bool CharacterTraits<char16_t>::IsSurrogatePair(ConstValue First, ConstValue Second) noexcept
	{
		return CharacterTraits<char16_t>::IsHighSurrogate(First) && CharacterTraits<char16_t>::IsLowSurrogate(Second);
	}

	inline constexpr System::uint8_t CharacterTraits<char16_t>::GetByteCount(ConstValue Value) noexcept
	{
		if (CharacterTraits<char16_t>::IsHighSurrogate(Value))
		{
			return 4_ui8;
		}
		else
		{	// unicode scalar value, low surrogate
			return 2_ui8;
		}
	}

	inline constexpr const bool CharacterTraits<wchar_t>::IsHighSurrogate(ConstValue Value) noexcept
	{
		return Value >= CharacterTraits<wchar_t>::HighSurrogateLimits[0] && Value <= CharacterTraits<wchar_t>::HighSurrogateLimits[1];
	}

	inline constexpr const bool CharacterTraits<wchar_t>::IsLowSurrogate(ConstValue Value) noexcept
	{
		return Value >= CharacterTraits<wchar_t>::LowSurrogateLimits[0] && Value <= CharacterTraits<wchar_t>::LowSurrogateLimits[1];
	}

	inline constexpr const bool CharacterTraits<wchar_t>::IsSurrogatePair(ConstValue First, ConstValue Second) noexcept
	{
		return CharacterTraits<wchar_t>::IsHighSurrogate(First) && CharacterTraits<wchar_t>::IsLowSurrogate(Second);
	}

	inline constexpr System::uint8_t CharacterTraits<wchar_t>::GetByteCount(ConstValue Value) noexcept
	{
		if (CharacterTraits<wchar_t>::IsHighSurrogate(Value))
		{
			return 4_ui8;
		}
		else
		{	// unicode scalar value, low surrogate
			return 2_ui8;
		}
	}
}
#endif
