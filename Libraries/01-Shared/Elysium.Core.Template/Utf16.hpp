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
		constexpr Utf16() noexcept = delete;

		constexpr Utf16(const Utf16& Source) = delete;

		constexpr Utf16(Utf16&& Right) noexcept = delete;

		constexpr ~Utf16() = delete;
	public:
		Utf16& operator=(const Utf16& Source) = delete;

		Utf16& operator=(Utf16&& Right) noexcept = delete;
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
	};

	template<>
	inline String<char> Utf16::FromSafeWideString(const wchar_t* Data, const System::size Length) noexcept
	{
		System::uint32_t CodePoint = 0;
		System::uint32_t RequiredLength = 0;
		for (System::size i = 0; i < Length; ++i)
		{
			if (CharacterTraits<wchar_t>::IsHighSurrogate(Data[i]))
			{
				RequiredLength++;
				i++;	// skip low surrogate
			}
			else
			{
				RequiredLength++;
			}
		}

		String<char> Result = String<char>(RequiredLength);
		for (System::size i = 0; i < Length; ++i)
		{
			// ToDo
		}
		
		return Result;
	}

	template<>
	inline String<char8_t> Utf16::FromSafeWideString(const wchar_t* Data, const System::size Length) noexcept
	{
		char32_t CodePoint;
		System::size RequiredLength = 0;
		for (System::size i = 0; i < Length; ++i)
		{
			CodePoint = CharacterTraits<wchar_t>::ConvertToUtf32((wchar_t*)&Data[i]);
			if (CodePoint < 0x80)			// 0 - 127
			{
				RequiredLength++;
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
					i++;	// skip low surrogate
				}
			}
			else if (CodePoint < 0x110000)	// 65536 - 1114111
			{
				RequiredLength += 4;
				i++;	// skip low surrogate (no check required as a number in this range will have to be represented by a high- and low-surrogate)
			}
		}

		String<char8_t> Result = String<char8_t>(RequiredLength);
		System::byte* Byte1 = nullptr;
		System::byte* Byte2 = nullptr;
		System::byte* Byte3 = nullptr;
		System::uint32_t CharacterIndex = 0;
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
					i++;	// skip low surrogate
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
				i++;	// skip low surrogate (no check required as a number in this range will have to be represented by a high- and low-surrogate)
			}
		}

		return Result;
	}

	template<Concepts::Character C>
	inline String<C> Utf16::FromSafeWideString(const wchar_t* Data, const System::size Length) noexcept
	{	// ToDo: throw NotImplementedException($"Unhandled Character {typeof(C).FullName}");
		throw 1;
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
		char32_t CodePoint;
		System::size RequiredLength = 0;
		for (System::size i = 0; i < Length; ++i)
		{
			switch (CharacterTraits<char8_t>::GetByteCount(Data[i]))
			{
			case 1:		// 0xxx xxxx										->	0xxx xxxx
				RequiredLength++;
				break;
			case 2:		// 110y yyyy	10xx xxxx							->	0000 0yyy	yyxx xxxx
				RequiredLength++;
				i++;
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
				break;
			}
		}

		String<wchar_t> Result = String<wchar_t>(RequiredLength);
		System::size TargetIndex = 0;
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
				break;
			}
		}

		return Result;
	}

	template<Concepts::Character C>
	inline String<wchar_t> Utf16::SafeToWideString(const C* Data, const System::size Length) noexcept
	{	// ToDo: throw NotImplementedException($"Unhandled Character {typeof(C).FullName}");
		throw 1;
	}
}
#endif
