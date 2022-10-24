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

#ifndef ELYSIUM_CORE_TEMPLATE_NUMERIC_NUMERICLIMITS
#include "NumericLimits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_LITERALS
#include "Literals.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CHARACTERCATEGORY
#include "CharacterCategory.hpp"
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
		static constexpr ConstValue MinimumValue = static_cast<ConstValue>(Elysium::Core::Template::Numeric::NumericLimits<I>::Minimum);

		/// <summary>
		/// Returns the largest possible value as specified character-type.
		/// </summary>
		static constexpr ConstValue MaximumValue = static_cast<ConstValue>(Elysium::Core::Template::Numeric::NumericLimits<I>::Maximum);
	public:
		/// <summary>
		/// Indicates whether a character is categorized as an ASCII character ([ U+0000..U+007F ]).
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsAscii(ConstValue Value) noexcept;

		/// <summary>
		/// Indicates whether a character is categorized as a control character.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsControl(ConstValue Value) noexcept;

		/// <summary>
		/// Indicates whether a character is categorized as a decimal digit.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsDigit(ConstValue Value) noexcept;

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
	
	template<Concepts::Character C, Concepts::UnsignedInteger I>
	inline constexpr const bool CharacterTraitsBase<C, I>::IsAscii(ConstValue Value) noexcept
	{
		return static_cast<ConstInteger>(Value) < 0x80;
	}

	template<>
	inline constexpr const bool CharacterTraitsBase<char, unsigned char>::IsControl(ConstValue Value) noexcept
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
		return static_cast<ConstInteger>(Value) > 0x2F && static_cast<ConstInteger>(Value) < 0x3A;	// Radix-10 digits
	}

	template<>
	inline constexpr const bool CharacterTraitsBase<char, unsigned char>::IsHighAscii(ConstValue Value) noexcept
	{
		return Value >> 7 != 0x00;	// 1-xxx xxxx (128 - 255)
	}

	template<>
	inline constexpr const bool CharacterTraitsBase<char8_t, unsigned char>::IsHighAscii(ConstValue Value) noexcept
	{
		return Value >> 7 != 0x00;	// 1-xxx xxxx (128 - 255)
	}

	template<>
	inline constexpr const bool CharacterTraitsBase<char16_t, unsigned short>::IsHighAscii(ConstValue Value) noexcept
	{	// ToDo:
		return false;
	}

	template<>
	inline constexpr const bool CharacterTraitsBase<char32_t, unsigned int>::IsHighAscii(ConstValue Value) noexcept
	{	// ToDo:
		return false;
	}

	template<>
	inline constexpr const bool CharacterTraitsBase<wchar_t, unsigned short>::IsHighAscii(ConstValue Value) noexcept
	{	// ToDo:
		return false;
	}

	template<Concepts::Character C, Concepts::UnsignedInteger I>
	inline constexpr const bool CharacterTraitsBase<C, I>::IsHighAscii(ConstValue Value) noexcept
	{
		return false;
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
	inline constexpr CharacterTraitsBase<char8_t, unsigned char>::Pointer CharacterTraitsBase<char8_t, unsigned char>::Find(ConstPointer Start, const Elysium::Core::Template::System::size Length, ConstValue Value) noexcept
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
	inline constexpr CharacterTraitsBase<char16_t, unsigned short>::Pointer CharacterTraitsBase<char16_t, unsigned short>::Find(ConstPointer Start, const Elysium::Core::Template::System::size Length, ConstValue Value) noexcept
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
	inline constexpr CharacterTraitsBase<char32_t, unsigned int>::Pointer CharacterTraitsBase<char32_t, unsigned int>::Find(ConstPointer Start, const Elysium::Core::Template::System::size Length, ConstValue Value) noexcept
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
	inline constexpr CharacterTraitsBase<wchar_t, unsigned short>::Pointer CharacterTraitsBase<wchar_t, unsigned short>::Find(ConstPointer Start, const Elysium::Core::Template::System::size Length, ConstValue Value) noexcept
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
		if (Start == nullptr)
		{
			return 0;
		}

		Elysium::Core::Template::System::size Length = 0;
		while (*Start != NullTerminationCharacter)
		{
			Length++;
			Start++;
		}

		return Length;
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
	struct CharacterTraits<char> : public CharacterTraitsBase<char, unsigned char>
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
	public:
		//static constexpr const CharacterCategory GetCategory(ConstCharacter Value) noexcept;

		//static constexpr unsigned int ConvertToUtf32(ConstCharacter Value) noexcept;

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
		static constexpr const bool IsWhiteSpace(ConstValue Value) noexcept;

		//static constexpr C ToLower(ConstValue Value) noexcept;
		
		//static constexpr C ToLowerInvariant(ConstValue Value) noexcept;
		
		//static constexpr C ToUpper(ConstValue Value) noexcept;
		
		//static constexpr C ToUpperInvariant(ConstValue Value) noexcept;
	};

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

	inline constexpr const bool CharacterTraits<char>::IsWhiteSpace(CharacterTraits<char>::ConstValue Value) noexcept
	{
		return Value == 0x20;
	}

	/// <summary>
	/// 
	/// </summary>
	template <>
	struct CharacterTraits<wchar_t> : public CharacterTraitsBase<wchar_t, unsigned short>
	{
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
		//static constexpr const bool IsHighSurrogate(ConstValue Value) noexcept;

		//static constexpr const bool IsLowSurrogate(ConstValue Value) noexcept;
	};

	/// <summary>
	/// 
	/// </summary>
	template <>
	struct CharacterTraits<char8_t> : public CharacterTraitsBase<char8_t, unsigned char>
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
	};

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

	/// <summary>
	/// 
	/// </summary>
	template <>
	struct CharacterTraits<char16_t> : public CharacterTraitsBase<char16_t, unsigned short>
	{
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
		
		//static constexpr const bool IsHighSurrogate(ConstValue Value) noexcept;

		//static constexpr const bool IsLowSurrogate(ConstValue Value) noexcept;
	};

	/// <summary>
	/// 
	/// </summary>
	template <>
	struct CharacterTraits<char32_t> : public CharacterTraitsBase<char32_t, unsigned int>
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
		static constexpr const System::size MaximumByteLength = sizeof(char32_t);
	public:
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
	};

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
}
#endif
