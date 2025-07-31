/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UTF16
#define ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UTF16

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_CHARACTER
#include "Character.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CHARACTERTRAITS
#include "CharacterTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "String.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

namespace Elysium::Core::Template::Text::Unicode
{
	class Utf16 final
	{
	public:
		using Type = char16_t;
		using Pointer = char16_t*;
		using ConstType = const char16_t;
		using ConstPointer = const char16_t*;
		using ConstReference = const char16_t&;
		/*
		using Type = wchar_t;
		using Pointer = wchar_t*;
		using ConstType = const wchar_t;
		using ConstPointer = const wchar_t*;
		using ConstReference = const wchar_t&;
		*/
	public:
		constexpr Utf16() noexcept = delete;

		constexpr Utf16(const Utf16& Source) = delete;

		constexpr Utf16(Utf16&& Right) noexcept = delete;

		constexpr ~Utf16() = delete;
	public:
		Utf16& operator=(const Utf16& Source) = delete;

		Utf16& operator=(Utf16&& Right) noexcept = delete;
	public:
		inline static constexpr const Type ByteOrderMarkLittleEndian[] = { 0xFE, 0xFF, 0x00, 0x00 };

		inline static constexpr const Type ByteOrderMarkBigEndian[] = { 0xFF, 0xFE, 0x00, 0x00 };
	public:
		/// <summary>
		/// Returns whether given text is valid utf-16.
		/// (Make sure to use correct byte-order when calling this method!)
		/// </summary>
		/// <param name="Value"></param>
		/// <param name="Length"></param>
		/// <returns></returns>
		static constexpr const bool IsValid(ConstPointer Value, Elysium::Core::Template::System::size Length) noexcept;
	/*
	public:
		/// <summary>
		/// Returns the unicode code point representation.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const char32_t ConvertToUtf32(ConstPointer Value) noexcept;
	*/
	public:
		/// <summary>
		/// Returns the length required to convert given wchar_t* to C* while not performing any checks on the inputs integrity.
		/// </summary>
		/// <typeparam name="C"></typeparam>
		/// <param name="Data"></param>
		/// <returns></returns>
		template <Concepts::Character C>
		static constexpr System::size GetRequiredLengthOfSafeWideString(const wchar_t* Data, const System::size Length) noexcept;

		/// <summary>
		/// Returns the length required to convert given C* to wchar_t* while not performing any checks on the inputs integrity.
		/// </summary>
		/// <typeparam name="C"></typeparam>
		/// <param name="Data"></param>
		/// <param name="Length"></param>
		/// <returns></returns>
		template <Concepts::Character C>
		static constexpr System::size GetRequiredLengthForSafeWideString(const C* Data, const System::size Length) noexcept;
	public:
		/// <summary>
		/// Encodes given WideString to desired String while assuming the input to be correct and therefore performing no checks on it.
		/// Therefore a usage example is a WideString received from the operating system where the correctness can be expected.
		/// </summary>
		/// <param name="Data"></param>
		/// <param name="Size"></param>
		/// <returns></returns>
		template <Concepts::Character C>
		static String<C> FromSafeWideString(const wchar_t* Data, const System::size Length) noexcept;

		/// <summary>
		/// Encodes given String<C> to WideString while assuming the input to be correct and therefore performing no checks on it.
		/// </summary>
		/// <param name="Data"></param>
		/// <param name="Length"></param>
		/// <returns></returns>
		template <Concepts::Character C>
		static String<wchar_t> SafeToWideString(const C* Data, const System::size Length) noexcept;
	public:
		/*
		/// <summary>
		/// 
		/// </summary>
		/// <typeparam name="C"></typeparam>
		/// <param name="Data"></param>
		/// <param name="Length"></param>
		/// <returns></returns>
		template <Concepts::Character C>
		static String<C> FromWideString(const wchar_t* Data, const System::size Length);

		/// <summary>
		/// 
		/// </summary>
		/// <typeparam name="C"></typeparam>
		/// <param name="Data"></param>
		/// <param name="Length"></param>
		/// <returns></returns>
		template <Concepts::Character C>
		static String<wchar_t> ToWideString(const C* Data, const System::size Length);
		*/
	};

	inline constexpr const bool Elysium::Core::Template::Text::Unicode::Utf16::IsValid(ConstPointer Value, Elysium::Core::Template::System::size Length) noexcept
	{
		if (nullptr == Value || 0 == Length)
		{
			return true;
		}

		// ensure first char isn't a low surrogate
		if (CharacterTraits<Type>::IsLowSurrogate(Value[0]))
		{
			return false;
		}

		for (System::size i = 0; i < Length; ++i)
		{
			if (CharacterTraits<Type>::IsHighSurrogate(Value[i]))
			{
				if (++i > Length || !CharacterTraits<Type>::IsLowSurrogate(Value[i]))
				{
					return false;
				}
			}
			// else it's a char in bmp (basic multilingual plane)
		}

		return true;
	}
	
	template<>
	inline constexpr System::size Utf16::GetRequiredLengthOfSafeWideString<char>(const wchar_t* Data, const System::size Length) noexcept
	{
		System::uint32_t RequiredLength = 0;
		for (System::size i = 0; i < Length; ++i)
		{
			if (CharacterTraits<wchar_t>::IsHighSurrogate(Data[i]))
			{
				++RequiredLength;
				++i;	// skip low surrogate
			}
			else
			{
				++RequiredLength;
			}
		}

		return RequiredLength;
	}

	template<>
	inline constexpr System::size Utf16::GetRequiredLengthOfSafeWideString<char8_t>(const wchar_t* Data, const System::size Length) noexcept
	{
		char32_t CodePoint;	// afaik I cannot get rid of the codepoint
		System::size RequiredLength = 0;
		for (System::size i = 0; i < Length; ++i)
		{
			CodePoint = CharacterTraits<wchar_t>::ConvertToUtf32((wchar_t*)&Data[i]);
			if (CodePoint < 0x80)			// 0 - 127
			{
				++RequiredLength;
			}
			else if (CodePoint < 0x800)		// 128 - 2047
			{
				RequiredLength += 2;
			}
			else if (CodePoint < 0x10000)	// 2048 - 65535
			{
				RequiredLength += 3;
				if (CharacterTraits<wchar_t>::IsHighSurrogate(Data[i]))
				{
					++i;	// skip low surrogate
				}
			}
			else if (CodePoint < 0x110000)	// 65536 - 1114111
			{
				RequiredLength += 4;
				++i;	// skip low surrogate (no check required as a number in this range will have to be represented by a high- and low-surrogate)
			}
			else
			{
				// ToDo: this should never happen!
				//assert(false);
			}
		}

		return RequiredLength;
	}

	template<>
	inline constexpr System::size Utf16::GetRequiredLengthOfSafeWideString<char16_t>(const wchar_t* Data, const System::size Length) noexcept
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		return Length;
#else
		// @ToDo: on other operating systems char16_t might not be the same as wchar_t!
#error "undefined os"
#endif
	}

	template<>
	inline constexpr System::size Utf16::GetRequiredLengthOfSafeWideString<char32_t>(const wchar_t* Data, const System::size Length) noexcept
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		System::size RequiredLength = 0;
		for (System::size i = 0; i < Length; ++i)
		{
			++RequiredLength;
			if (CharacterTraits<wchar_t>::IsHighSurrogate(Data[i]))
			{
				++i;	// skip low surrogate
			}
		}

		return RequiredLength;
#elif defined ELYSIUM_CORE_OS_LINUX
		return Length;	// wchar_t is 4 bytes on linux and mapped to UTF-32
#else
		// @ToDo: on other operating systems char16_t might not be the same as wchar_t!
#error "undefined os"
#endif
	}

	template<>
	inline constexpr System::size Utf16::GetRequiredLengthOfSafeWideString<wchar_t>(const wchar_t* Data, const System::size Length) noexcept
	{
		return Length;
	}

	template<Concepts::Character C>
	inline constexpr System::size Utf16::GetRequiredLengthOfSafeWideString(const wchar_t* Data, const System::size Length) noexcept
	{
		return -1;
	}

	template<>
	inline constexpr System::size Utf16::GetRequiredLengthForSafeWideString(const char* Data, const System::size Length) noexcept
	{
		return Length;
	}

	template<>
	inline constexpr System::size Utf16::GetRequiredLengthForSafeWideString(const char8_t* Data, const System::size Length) noexcept
	{
		char32_t CodePoint;	// afaik I cannot get rid of the codepoint
		System::size RequiredLength = 0;
		for (System::size i = 0; i < Length; ++i)
		{
			switch (CharacterTraits<char8_t>::GetByteCount(Data[i]))
			{
			case 1:		// 0xxx xxxx										->	0xxx xxxx
				++RequiredLength;
				break;
			case 2:		// 110y yyyy	10xx xxxx							->	0000 0yyy	yyxx xxxx
				++RequiredLength;
				++i;
				break;
			case 3:		// 1110 zzzz	10yy yyyy	10xx xxxx				->	zzzz yyyy	yyxx xxxx
				CodePoint = CharacterTraits<char8_t>::ConvertToUtf32(&Data[i]);
				if (CodePoint >= 0xD800 && CodePoint <= 0xDBFF)
				{
					RequiredLength += 4;
					i += 3;
				}
				else
				{
					RequiredLength += 2;
					i += 2;
				}
				break;
			case 4:		// 1111 0aaa	10zz zzzz	10yy yyyyy	10xx xxxx	->	000a aazz	zzzz yyyy	yyxx xxxx
				RequiredLength += 4;
				i += 3;
				break;
			default:	// 10xx xxxx (trail byte. determination not possible)
				// ToDo: this should never happen!
				//assert(false);
				break;
			}
		}

		return RequiredLength;
	}

	template<>
	inline constexpr System::size Utf16::GetRequiredLengthForSafeWideString(const char16_t* Data, const System::size Length) noexcept
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		return Length;
#else
		// @ToDo: on other operating systems char16_t might not be the same as wchar_t!
#error "undefined os"
#endif
	}

	template<>
	inline constexpr System::size Utf16::GetRequiredLengthForSafeWideString(const char32_t* Data, const System::size Length) noexcept
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		System::size RequiredLength = 0;
		char32_t CodePoint;
		for (System::size i = 0; i < Length; ++i)
		{
			CodePoint = Data[i];
			if (CodePoint <= 0xFFFF)
			{	// basic multilingual plane (BMP)
				++RequiredLength;
			}
			else if (CodePoint <= 0x10FFFF)
			{	// surrogate pair
				RequiredLength += 2;
			}
		}

		return RequiredLength;
#elif defined ELYSIUM_CORE_OS_LINUX
		return Length;	// wchar_t is 4 bytes on linux and mapped to UTF-32
#else
		// @ToDo: on other operating systems char16_t might not be the same as wchar_t!
#error "undefined os"
#endif
	}

	template<>
	inline constexpr System::size Utf16::GetRequiredLengthForSafeWideString(const wchar_t* Data, const System::size Length) noexcept
	{
		return Length;
	}

	template<Concepts::Character C>
	inline constexpr System::size Utf16::GetRequiredLengthForSafeWideString(const C* Data, const System::size Length) noexcept
	{
		return -1;
	}

	template<>
	inline String<char> Utf16::FromSafeWideString(const wchar_t* Data, const System::size Length) noexcept
	{
		static constexpr const char InvalidCharacterRepresentation = '?';

		const System::size RequiredLength = GetRequiredLengthOfSafeWideString<wchar_t>(Data, Length);

		String<char> Result = String<char>(RequiredLength);
		for (System::size i = 0; i < Length; ++i)
		{
			if (CharacterTraits<wchar_t>::IsHighSurrogate(Data[i]))
			{
				Result[i] = InvalidCharacterRepresentation;
				++i;	// skip low surrogate
			}
			else if (Data[i] > 0x80)
			{
				Result[i] = InvalidCharacterRepresentation;
			}
			else
			{
				Result[i] = Data[i];
			}

			++i;
		}
		
		return Result;
	}

	template<>
	inline String<char8_t> Utf16::FromSafeWideString(const wchar_t* Data, const System::size Length) noexcept
	{
		const System::size RequiredLength = GetRequiredLengthOfSafeWideString<wchar_t>(Data, Length);

		String<char8_t> Result = String<char8_t>(RequiredLength);
		char32_t CodePoint;	// afaik I cannot get rid of the codepoint
		System::byte* Byte1 = nullptr;
		System::byte* Byte2 = nullptr;
		System::byte* Byte3 = nullptr;
		System::size CharacterIndex = 0;

		for (System::size i = 0; i < Length; ++i)
		{
			CodePoint = CharacterTraits<wchar_t>::ConvertToUtf32((wchar_t*)&Data[i]);
			if (CodePoint < 0x80)			// 0 - 127
			{
				// 0xxx xxxx									->	0xxx xxxx
				Result[CharacterIndex++] = static_cast<System::uint8_t>(CodePoint);
			}
			else if (CodePoint < 0x800)		// 128 - 2047
			{
				// 0000 0yyy	yyxx xxxx						->	110y yyyy	10xx xxxx
				Byte1 = (System::byte*)&CodePoint;
				Byte2 = &Byte1[1];

				Result[CharacterIndex++] = 0xC0 | (*Byte2 << 2) | (*Byte1 >> 6);
				Result[CharacterIndex++] = 0x80 | (*Byte1 & 0x3F);
			}
			else if (CodePoint < 0x10000)	// 2048 - 65535
			{
				// zzzz yyyy	yyxx xxxx						->	1110 zzzz	10yy yyyy	10xx xxxx
				Byte1 = (System::byte*)&CodePoint;
				Byte2 = &Byte1[1];

				Result[CharacterIndex++] = 0xE0 | (*Byte2 >> 4);
				Result[CharacterIndex++] = 0x80 | ((*Byte2 & 0x0F) << 2) | (*Byte1 >> 6);
				Result[CharacterIndex++] = 0x80 | (*Byte1 & 0x3F);
				if (CharacterTraits<wchar_t>::IsHighSurrogate(Data[i]))
				{
					++i;	// skip low surrogate
				}
			}
			else if (CodePoint < 0x110000)	// 65536 - 1114111
			{
				// 000a aazz	zzzz yyyy	yyxx xxxx			->	1111 0aaa	10zz zzzz	10yy yyyyy	10xx xxxx
				Byte1 = (System::byte*)&CodePoint;
				Byte2 = &Byte1[1];
				Byte3 = &Byte1[2];

				Result[CharacterIndex++] = 0xF0 | ((*Byte3 & 0x1F) >> 2);
				Result[CharacterIndex++] = 0x80 | ((*Byte3 & 0x03) << 4) | (*Byte2 >> 4);
				Result[CharacterIndex++] = 0x80 | ((*Byte2 & 0x0F) << 2) | (*Byte1 >> 6);
				Result[CharacterIndex++] = 0x80 | (*Byte1 & 0x3F);
				++i;	// skip low surrogate (no check required as a number in this range will have to be represented by a high- and low-surrogate)
			}
			else
			{
				// ToDo: this should never happen!
				//assert(false);
			}
		}

		return Result;
	}

	template<>
	inline String<char16_t> Utf16::FromSafeWideString(const wchar_t* Data, const System::size Length) noexcept
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		String<char16_t> Result = String<char16_t>(Length);
		memcpy(&Result[0], Data, Length * CharacterTraits<wchar_t>::MinimumByteLength);

		return Result;
#else
		// @ToDo: on other operating systems char16_t might not be the same as wchar_t!
#error "undefined os"
#endif
	}

	template<>
	inline String<char32_t> Utf16::FromSafeWideString(const wchar_t* Data, const System::size Length) noexcept
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		const System::size RequiredLength = GetRequiredLengthOfSafeWideString<wchar_t>(Data, Length);

		String<char32_t> Result = String<char32_t>(RequiredLength);
		for (System::size i = 0; i < Length; ++i)
		{
			Result[i] = CharacterTraits<wchar_t>::ConvertToUtf32(&Data[i]);
			if (CharacterTraits<wchar_t>::IsHighSurrogate(Data[i]))
			{
				++i;	// skip low surrogate
			}
		}

		return Result;
#elif defined ELYSIUM_CORE_OS_LINUX
		return String<char32_t>(Data, Length);	// wchar_t is 4 bytes on linux and mapped to UTF-32
#else
		// @ToDo: on other operating systems char16_t might not be the same as wchar_t!
#error "undefined os"
#endif
	}

	template<>
	inline String<wchar_t> Utf16::FromSafeWideString(const wchar_t* Data, const System::size Length) noexcept
	{
		return String<wchar_t>(Data, Length);
	}

	template<Concepts::Character C>
	inline String<C> Utf16::FromSafeWideString(const wchar_t* Data, const System::size Length) noexcept
	{
		return String<C>();
	}

	template<>
	inline String<wchar_t> Utf16::SafeToWideString(const char* Data, const System::size Length) noexcept
	{
		String<wchar_t> Result = String<wchar_t>(Length);
		for (System::size i = 0; i < Length; i++)
		{
			Result[i] = Data[i];
		}

		return Result;
	}

	template<>
	inline String<wchar_t> Utf16::SafeToWideString(const char8_t* Data, const System::size Length) noexcept
	{
		const System::size RequiredLength = GetRequiredLengthForSafeWideString<char8_t>(Data, Length);

		String<wchar_t> Result = String<wchar_t>(RequiredLength);
		System::size TargetIndex = 0;
		char32_t CodePoint;	// afaik I cannot get rid of the codepoint
		System::byte* CodePointBytes;
		for (System::size i = 0; i < Length; ++i)
		{
			const wchar_t& CurrentTargetChar = Result[TargetIndex];
			const char8_t& CurrentChar = Data[i];

			switch (CharacterTraits<char8_t>::GetByteCount(Data[i]))
			{
			case 1:		// 0xxx xxxx										->	0xxx xxxx
				Result[TargetIndex++] = Data[i];
				break;
			case 2:		// 110y yyyy	10xx xxxx							->	0000 0yyy	yyxx xxxx
				/*
				* ToDo: these aren't bytes but wchar_ts!
				Result[TargetIndex] = ((Data[i] & 0x03) << 6) | (Data[i + 1] & 0x3F);
				Result[++TargetIndex] = (Data[i] >> 2) & 0x07;
				*/
				i++;
				break;
			case 3:		// 1110 zzzz	10yy yyyy	10xx xxxx				->	zzzz yyyy	yyxx xxxx
				CodePoint = CharacterTraits<char8_t>::ConvertToUtf32(&Data[i]);
				if (CodePoint >= 0xD800 && CodePoint <= 0xDBFF)
				{
					/*
					U' = zzzz zzzz	xxxx xxyy	.... aabb .... ....  // U - 0x10000
					W1 = 1101 10aa	bbxx xxxx      // 0xD800 + yyyyyyyyyy
					W2 = 1101 11yy	zzzz zzzz      // 0xDC00 + xxxxxxxxxx
					*/
					CodePoint -= 0x10000;
					CodePointBytes = (System::byte*)&CodePoint;
					/*
					* ToDo: these aren't bytes but wchar_ts!
					Result[TargetIndex] = ((CodePointBytes[2] & 0x03) << 6) | CodePointBytes[1] >> 2;
					Result[++TargetIndex] = 0xD8 | ((CodePointBytes[2] >> 2) & 0x03);
					Result[++TargetIndex] = CodePointBytes[0];
					Result[++TargetIndex] = 0xDC | (CodePointBytes[1] & 0x03);
					i += 3;
					*/
				}
				else
				{
					/*
					* ToDo: these aren't bytes but wchar_ts!
					CodePointBytes = (System::byte*)&CodePoint;
					Result[TargetIndex] = CodePointBytes[0];
					Result[++TargetIndex] = CodePointBytes[1];
					*/
					i += 2;
				}
				break;
			case 4:		// 1111 0aaa	10zz zzzz	10yy yyyyy	10xx xxxx	->	000a aazz	zzzz yyyy	yyxx xxxx
				/*
				U' = zzzz zzzz	xxxx xxyy	.... aabb .... ....  // U - 0x10000
				W1 = 1101 10aa	bbxx xxxx      // 0xD800 + yyyyyyyyyy
				W2 = 1101 11yy	zzzz zzzz      // 0xDC00 + xxxxxxxxxx
				*/
				CodePoint = CharacterTraits<char8_t>::ConvertToUtf32(&Data[i]);
				CodePoint -= 0x10000;
				CodePointBytes = (System::byte*)&CodePoint;
				/*
				* ToDo: these aren't bytes but wchar_ts!
				Result[TargetIndex] = ((CodePointBytes[2] & 0x03) << 6) | CodePointBytes[1] >> 2;
				Result[++TargetIndex] = 0xD8 | ((CodePointBytes[2] >> 2) & 0x03);
				Result[++TargetIndex] = CodePointBytes[0];
				Result[++TargetIndex] = 0xDC | (CodePointBytes[1] & 0x03);
				*/
				i += 3;
				break;
			default:	// 10xx xxxx (trail byte. determination not possible)
				// ToDo: this should never happen!
				//assert(false);
				break;
			}
		}

		return Result;
	}

	template<>
	inline String<wchar_t> Utf16::SafeToWideString(const char16_t* Data, const System::size Length) noexcept
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		String<wchar_t> Result = String<wchar_t>(Length);
		memcpy(&Result[0], Data, Length * CharacterTraits<char16_t>::MinimumByteLength);

		return Result;
#else
		// @ToDo: on other operating systems char16_t might not be the same as wchar_t!
#error "undefined os"
#endif
	}

	template<>
	inline String<wchar_t> Utf16::SafeToWideString(const char32_t* Data, const System::size Length) noexcept
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		const System::size RequiredLength = GetRequiredLengthForSafeWideString<char32_t>(Data, Length);

		String<wchar_t> Result = String<wchar_t>(RequiredLength);
		char32_t CodePoint;
		for (System::size i = 0; i < Length; ++i)
		{
			CodePoint = Data[i];
			if (CodePoint <= 0xFFFF)
			{	// basic multilingual plane (BMP)
				Result[i] = static_cast<wchar_t>(CodePoint);
				/*
				if (CodePoint >= 0xD800 && CodePoint <= 0xDFFF)
				{
					// ToDo: this should never happen!
					//assert(false);
				}
				*/
			}
			else if (CodePoint <= 0x10FFFF)
			{	// surrogate pair
				CodePoint -= 0x10000;

				Result[i] = 0xD800 + ((CodePoint >> 10) & 0x3FF);
				Result[++i] = 0xDC00 + (CodePoint & 0x3FF);	// @ToDo: ++i PROBLEM! <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			}
			/*
			else
			{
				// ToDo: this should never happen!
				//assert(false);
			}
			*/
		}

		return Result;
#elif defined ELYSIUM_CORE_OS_LINUX
		return String<wchar_t>(Data, Length);	// wchar_t is 4 bytes on linux and mapped to UTF-32
#else
		// @ToDo: on other operating systems char16_t might not be the same as wchar_t!
#error "undefined os"
#endif
	}

	template<>
	inline String<wchar_t> Utf16::SafeToWideString(const wchar_t* Data, const System::size Length) noexcept
	{
		return String<wchar_t>(Data, Length);
	}

	template<Concepts::Character C>
	inline String<wchar_t> Utf16::SafeToWideString(const C* Data, const System::size Length) noexcept
	{
		return String<wchar_t>();
	}
}
#endif
