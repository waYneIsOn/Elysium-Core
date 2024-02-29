/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_ENCODING
#define ELYSIUM_CORE_TEMPLATE_TEXT_ENCODING

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_CHARACTER
#include "Character.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_COMMON_ENABLEIF
#include "EnableIf.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_SWAP
#include "Swap.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "OperatingSystem.hpp"
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

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISSAME
#include "IsSame.hpp"
#endif

namespace Elysium::Core::Template::Text
{
	class Encoding
	{
	public:
		Encoding() = delete;

		Encoding(const Encoding& Source) = delete;

		Encoding(Encoding&& Right) noexcept = delete;

		~Encoding() = delete;
	public:
		Encoding& operator=(const Encoding& Source) = delete;

		Encoding& operator=(Encoding&& Right) noexcept = delete;
	public:
		/// <summary>
		/// 
		/// </summary>
		inline static constexpr const System::byte Utf8Preamble[3] = { 0xEF, 0xBB, 0xBF };

		/// <summary>
		/// 
		/// </summary>
		inline static constexpr const System::byte Utf16LittleEndianPreamble[2] = { 0xFF, 0xFE };

		/// <summary>
		/// 
		/// </summary>
		inline static constexpr const System::byte Utf16BigEndianPreamble[2] = { 0xFE, 0xFF };

		/// <summary>
		/// 
		/// </summary>
		inline static constexpr const System::byte Utf32LittleEndianPreamble[4] = { 0xFF, 0xFE, 0x00, 0x00 };

		/// <summary>
		/// 
		/// </summary>
		inline static constexpr const System::byte Utf32BigEndianPreamble[4] = { 0x00, 0x00, 0xFE, 0xFF };
	public:
		template <class C, class Traits = CharacterTraits<C>>
		static Elysium::Core::Template::Text::String<C> FromWideString(const Elysium::Core::Template::Text::String<wchar_t>& Input);

		template <class C, class Traits = CharacterTraits<C>>
		static Elysium::Core::Template::Text::String<wchar_t> ToWideString(const Elysium::Core::Template::Text::String<C>& Input);
	public:
		template <class C, class Traits = CharacterTraits<C>>
		static Elysium::Core::Template::Text::String<char> ToANSIString(const Elysium::Core::Template::Text::String<C>& Input);

		template <class C, class Traits = CharacterTraits<C>>
		static Elysium::Core::Template::Text::String<char> ToASCIIString(const Elysium::Core::Template::Text::String<C>& Input);
	};

	template<>
	inline Elysium::Core::Template::Text::String<char> Encoding::FromWideString(const Elysium::Core::Template::Text::String<wchar_t>& Input)
	{
		throw 1;
	}

	template<>
	inline Elysium::Core::Template::Text::String<char8_t> Encoding::FromWideString(const Elysium::Core::Template::Text::String<wchar_t>& Input)
	{
		const System::size Length = Input.GetLength();

		throw 1;
	}

	template<>
	inline Elysium::Core::Template::Text::String<char16_t> Encoding::FromWideString(const Elysium::Core::Template::Text::String<wchar_t>& Input)
	{
		throw 1;
	}

	template<>
	inline Elysium::Core::Template::Text::String<char32_t> Encoding::FromWideString(const Elysium::Core::Template::Text::String<wchar_t>& Input)
	{
		throw 1;
	}

	template<>
	inline Elysium::Core::Template::Text::String<wchar_t> Encoding::FromWideString(const Elysium::Core::Template::Text::String<wchar_t>& Input)
	{
		return Input;
	}

	template<class C, class Traits>
	inline Elysium::Core::Template::Text::String<C> Encoding::FromWideString(const Elysium::Core::Template::Text::String<wchar_t>& Input)
	{
		return String<C>();
	}

	template<>
	inline Elysium::Core::Template::Text::String<wchar_t> Encoding::ToWideString(const Elysium::Core::Template::Text::String<char>& Input)
	{
		const System::size RequiredLength = Input.GetLength();
		String<wchar_t> Result = String<wchar_t>(RequiredLength);
		for (System::size i = 0; i < RequiredLength; i++)
		{
			Result[i] = Input[i];
		}

		return Result;
	}

	template<>
	inline Elysium::Core::Template::Text::String<wchar_t> Encoding::ToWideString(const Elysium::Core::Template::Text::String<char8_t>& Input)
	{
		const Elysium::Core::Template::System::size Length = Input.GetLength();
		System::uint32_t CodePoint;
		System::size RequiredLength = 0;
		for (Elysium::Core::Template::System::size i = 0; i < Length; ++i)
		{
			if (Input[i] >> 7 == 0x00)
			{	// 0-xxx xxxx											07 bit
				RequiredLength++;
			}
			else if (Input[i] >> 5 == 0x06)
			{	// 110-x xxyy	10-yy yyyy								11 bit
				RequiredLength++;
				i++;
			}
			else if (Input[i] >> 4 == 0x0E)
			{	// 1110 xxxx	10-xx xxyy	10-yy yyyy					16 bit
				CodePoint = ((((Input[i] & 0x0F) << 4) | ((Input[i + 1] >> 2) & 0x0F)) << 8) |
					(((Input[i + 1] & 0x03) << 6) | Input[i + 2] & 0x3F);
				if (CodePoint >= 0xD800 && CodePoint <= 0xDBFF)
				{
					RequiredLength += 2;
					i += 3;
				}
				else
				{
					RequiredLength++;
					i += 2;
				}
			}
			else if (Input[i] >> 3 == 0x1E)
			{	// 1111 0-xxx	10-xx yyyy	10-yy yyzz	10-zz zzzz		21 bit
				RequiredLength += 2;
				i += 3;
			}
			else
			{	// ToDo
				throw 1;
			}
		}

		String<wchar_t> Result = String<wchar_t>(RequiredLength);
		System::byte* CurrentByte = (System::byte*)&Result[0];
		System::byte* CodePointBytes;
		for (System::size i = 0; i < Length; i++)
		{
#if defined ELYSIUM_CORE_LITTLEENDIAN
			if (Input[i] >> 7 == 0x00)
			{	// 0-xxx xxxx											07 bit
				CurrentByte[0] = Input[i];
				CurrentByte[1] = 0x00;
				CurrentByte += 2;
			}
			else if (Input[i] >> 5 == 0x06)
			{	// 110-x xxxx	10-xx xyyy								11 bit
				CurrentByte[0] = ((Input[i] & 0x03) << 6) | (Input[i + 1] & 0x3F);
				CurrentByte[1] = (Input[i] >> 2) & 0x07;
				CurrentByte += 2;
				i++;
			}
			else if (Input[i] >> 4 == 0x0E)
			{	// 1110 xxxx	10-xx xxyy	10-yy yyyy					16 bit
				CodePoint = ((((Input[i] & 0x0F) << 4) | ((Input[i + 1] >> 2) & 0x0F)) << 8) |
					(((Input[i + 1] & 0x03) << 6) | Input[i + 2] & 0x3F);
				if (CodePoint >= 0xD800 && CodePoint <= 0xDBFF)
				{
					/*
					U' = zzzz zzzz	xxxx xxyy	.... aabb .... ....  // U - 0x10000
					W1 = 1101 10aa	bbxx xxxx      // 0xD800 + yyyyyyyyyy
					W2 = 1101 11yy	zzzz zzzz      // 0xDC00 + xxxxxxxxxx
					*/
					CodePoint -= 0x10000;
					CodePointBytes = (System::byte*)&CodePoint;

					CurrentByte[0] = ((CodePointBytes[2] & 0x03) << 6) | CodePointBytes[1] >> 2;
					CurrentByte[1] = 0xD8 | ((CodePointBytes[2] >> 2) & 0x03);
					CurrentByte[2] = CodePointBytes[0];
					CurrentByte[3] = 0xDC | (CodePointBytes[1] & 0x03);
					CurrentByte += 4;
					i += 3;
				}
				else
				{
					CodePointBytes = (System::byte*)&CodePoint;
					CurrentByte[0] = CodePointBytes[0];
					CurrentByte[1] = CodePointBytes[1];
					CurrentByte += 2;
					i += 2;
				}
			}
			else if (Input[i] >> 3 == 0x1E)
			{	// 1111 0-xxx	10-xx yyyy	10-yy yyzz	10-zz zzzz		21 bit
				CodePoint = ((((Input[i] & 0x07) << 2) | ((Input[i + 1] >> 4) & 0x03)) << 16) |
					((((Input[i + 1] & 0x0F) << 4) | ((Input[i + 2] >> 2) & 0x0F)) << 8) |
					(((Input[i + 2] & 0x03) << 6) | (Input[i + 3] & 0x3F));
				/*
				U' = zzzz zzzz	xxxx xxyy	.... aabb .... ....  // U - 0x10000
				W1 = 1101 10aa	bbxx xxxx      // 0xD800 + yyyyyyyyyy
				W2 = 1101 11yy	zzzz zzzz      // 0xDC00 + xxxxxxxxxx
				*/
				CodePoint -= 0x10000;
				CodePointBytes = (System::byte*)&CodePoint;

				CurrentByte[0] = ((CodePointBytes[2] & 0x03) << 6) | CodePointBytes[1] >> 2;
				CurrentByte[1] = 0xD8 | ((CodePointBytes[2] >> 2) & 0x03);
				CurrentByte[2] = CodePointBytes[0];
				CurrentByte[3] = 0xDC | (CodePointBytes[1] & 0x03);
				CurrentByte += 4;
				i += 3;
			}
			else
			{	// ToDo
				throw 1;
			}
#else
			if (Input[i] >> 7 == 0x00)
			{	// 0-xxx xxxx											07 bit
				CurrentByte[0] = 0x00;
				CurrentByte[1] = Input[i];
				CurrentByte += 2;
			}
			else if (Input[i] >> 5 == 0x06)
			{	// 110-x xxyy	10-yy yyyy								11 bit
				CurrentByte[0] = (Input[i] >> 2) & 0x07;
				CurrentByte[1] = ((Input[i] & 0x03) << 6) | (Input[++i] & 0x3F);
				CurrentByte += 2;
			}
			else if (Input[i] >> 4 == 0x0E)
			{	// 1110 xxxx	10-xx xxyy	10-yy yyyy					16 bit
				CodePoint = ((((Input[i] & 0x0F) << 4) | ((Input[i + 1] >> 2) & 0x0F)) << 8) |
					(((Input[i + 1] & 0x03) << 6) | Input[i + 2] & 0x3F);
				if (CodePoint >= 0xD800 && CodePoint <= 0xDBFF)
				{
					/*
					U' = zzzz zzzz	xxxx xxyy	.... aabb .... ....  // U - 0x10000
					W1 = 1101 10aa	bbxx xxxx      // 0xD800 + yyyyyyyyyy
					W2 = 1101 11yy	zzzz zzzz      // 0xDC00 + xxxxxxxxxx
					*/
					CodePoint -= 0x10000;
					CodePointBytes = (System::byte*)&CodePoint;

					CurrentByte[0] = 0xD8 | ((CodePointBytes[2] >> 2) & 0x03);
					CurrentByte[1] = ((CodePointBytes[2] & 0x03) << 6) | CodePointBytes[1] >> 2;
					CurrentByte[2] = 0xDC | (CodePointBytes[1] & 0x03);
					CurrentByte[3] = CodePointBytes[0];
					CurrentByte += 4;
					i += 3;
				}
				else
				{
					CodePointBytes = (System::byte*)&CodePoint;
					CurrentByte[0] = CodePointBytes[1];
					CurrentByte[1] = CodePointBytes[0];
					CurrentByte += 2;
					i += 2;
				}
			}
			else if (Input[i] >> 3 == 0x1E)
			{	// 1111 0-xxx	10-xx yyyy	10-yy yyzz	10-zz zzzz		21 bit
				CodePoint = ((((Input[i] & 0x07) << 2) | ((Input[i + 1] >> 4) & 0x03)) << 16) |
					((((Input[i + 1] & 0x0F) << 4) | ((Input[i + 2] >> 2) & 0x0F)) << 8) |
					(((Input[i + 2] & 0x03) << 6) | (Input[i + 3] & 0x3F));
				/*
				U' = zzzz zzzz	xxxx xxyy	.... aabb .... ....  // U - 0x10000
				W1 = 1101 10aa	bbxx xxxx      // 0xD800 + yyyyyyyyyy
				W2 = 1101 11yy	zzzz zzzz      // 0xDC00 + xxxxxxxxxx
				*/
				CodePoint -= 0x10000;
				CodePointBytes = (System::byte*)&CodePoint;

				CurrentByte[0] = 0xD8 | ((CodePointBytes[2] >> 2) & 0x03);
				CurrentByte[1] = ((CodePointBytes[2] & 0x03) << 6) | CodePointBytes[1] >> 2;
				CurrentByte[2] = 0xDC | (CodePointBytes[1] & 0x03);
				CurrentByte[3] = CodePointBytes[0];
				CurrentByte += 4;
				i += 3;
			}
			else
			{	// ToDo
				throw 1;
			}
#endif
		}

		return Result;
	}

	template<>
	inline Elysium::Core::Template::Text::String<wchar_t> Encoding::ToWideString(const Elysium::Core::Template::Text::String<char16_t>& Input)
	{
		const System::size RequiredLength = Input.GetLength();
		String<wchar_t> Result = String<wchar_t>(RequiredLength);
		for (System::size i = 0; i < RequiredLength; i++)
		{
			Result[i] = Input[i];
#if not defined ELYSIUM_CORE_LITTLEENDIAN
#error "untested"
			System::byte* FirstByte = (System::byte*)&Result[i];
			System::byte* SecondByte = FirstByte++;

			Functional::Swap(FirstByte, SecondByte);
#endif
		}

		return Result;
	}

	template<>
	inline Elysium::Core::Template::Text::String<wchar_t> Encoding::ToWideString(const Elysium::Core::Template::Text::String<char32_t>& Input)
	{
		throw 1;
	}

	template<>
	inline Elysium::Core::Template::Text::String<wchar_t> Encoding::ToWideString(const Elysium::Core::Template::Text::String<wchar_t>& Input)
	{
		return Input;
	}

	template<class C, class Traits>
	inline Elysium::Core::Template::Text::String<wchar_t> Encoding::ToWideString(const Elysium::Core::Template::Text::String<C>& Input)
	{
		return String<wchar_t>();
	}

	template<>
	inline Elysium::Core::Template::Text::String<char> Encoding::ToANSIString(const Elysium::Core::Template::Text::String<char>& Input)
	{
		return Input;
	}

	template<>
	inline Elysium::Core::Template::Text::String<char> Encoding::ToANSIString(const Elysium::Core::Template::Text::String<char8_t>& Input)
	{
		throw 1;
	}

	template<>
	inline Elysium::Core::Template::Text::String<char> Encoding::ToANSIString(const Elysium::Core::Template::Text::String<char16_t>& Input)
	{
		throw 1;
	}

	template<>
	inline Elysium::Core::Template::Text::String<char> Encoding::ToANSIString(const Elysium::Core::Template::Text::String<char32_t>& Input)
	{
		throw 1;
	}

	template<>
	inline Elysium::Core::Template::Text::String<char> Encoding::ToANSIString(const Elysium::Core::Template::Text::String<wchar_t>& Input)
	{
		throw 1;
	}

	template<>
	inline Elysium::Core::Template::Text::String<char> Encoding::ToASCIIString(const Elysium::Core::Template::Text::String<char>& Input)
	{
		String<char> Result = String<char>(Input);
		for (System::size i = 0; i < Result.GetLength(); i++)
		{
			Result[i] = CharacterTraits<char>::IsAscii(Input[i]) ? Input[i] : 0x3F;
		}

		return Result;
	}

	template<>
	inline Elysium::Core::Template::Text::String<char> Encoding::ToASCIIString(const Elysium::Core::Template::Text::String<char8_t>& Input)
	{
		const System::size InputLength = Input.GetLength();
		System::size RequiredLength = 0;
		Elysium::Core::Template::System::uint32_t CodePoint;
		for (System::size i = 0; i < InputLength; i++)
		{
			bool bla = Text::CharacterTraits<char8_t>::IsAscii(Input[i]);

			if (Input[i] >> 7 == 0x00)
			{	// 0-xxx xxxx											07 bit
				RequiredLength++;
			}
			else if (Input[i] >> 5 == 0x06)
			{	// 110-x xxyy	10-yy yyyy								11 bit
				RequiredLength++;
				i++;
			}
			else if (Input[i] >> 4 == 0x0E)
			{	// 1110 xxxx	10-xx xxyy	10-yy yyyy					16 bit
				CodePoint = ((((Input[i] & 0x0F) << 4) | ((Input[i + 1] >> 2) & 0x0F)) << 8) |
					(((Input[i + 1] & 0x03) << 6) | Input[i + 2] & 0x3F);
				if (CodePoint >= 0xD800 && CodePoint <= 0xDBFF)
				{
					RequiredLength++;
					i += 3;
				}
				else
				{
					RequiredLength++;
					i += 2;
				}
			}
			else if (Input[i] >> 3 == 0x1E)
			{	// 1111 0-xxx	10-xx yyyy	10-yy yyzz	10-zz zzzz		21 bit
				RequiredLength++;
				i += 3;
			}
		}

		String<char> Result = String<char>(RequiredLength);
		System::size ResultIndex = 0;
		for (System::size i = 0; i < InputLength; i++)
		{
			if (Input[i] >> 7 == 0x00)
			{	// 0-xxx xxxx											07 bit
				Result[ResultIndex++] = Input[i];
			}
			else if (Input[i] >> 5 == 0x06)
			{	// 110-x xxyy	10-yy yyyy								11 bit
				Result[ResultIndex++] = 0x3F;
				i++;
			}
			else if (Input[i] >> 4 == 0x0E)
			{	// 1110 xxxx	10-xx xxyy	10-yy yyyy					16 bit
				CodePoint = ((((Input[i] & 0x0F) << 4) | ((Input[i + 1] >> 2) & 0x0F)) << 8) |
					(((Input[i + 1] & 0x03) << 6) | Input[i + 2] & 0x3F);
				if (CodePoint >= 0xD800 && CodePoint <= 0xDBFF)
				{
					Result[ResultIndex++] = 0x3F;
					i += 3;
				}
				else
				{
					Result[ResultIndex++] = 0x3F;
					i += 2;
				}
			}
			else if (Input[i] >> 3 == 0x1E)
			{	// 1111 0-xxx	10-xx yyyy	10-yy yyzz	10-zz zzzz		21 bit
				Result[ResultIndex++] = 0x3F;
				i += 3;
			}
		}

		return Result;
	}

	template<>
	inline Elysium::Core::Template::Text::String<char> Encoding::ToASCIIString(const Elysium::Core::Template::Text::String<char16_t>& Input)
	{
		const System::size RequiredLength = Input.GetLength();
		System::byte* Data = (System::byte*)&Input[0];
		Elysium::Core::Template::System::uint16_t IntegerRepresentation;
		String<char> Result = String<char>(RequiredLength);
		for (System::size i = 0; i < RequiredLength; i++)
		{
			IntegerRepresentation = Input[i];
			Result[i] = IntegerRepresentation < 0x80 ? static_cast<char>(IntegerRepresentation) : 0x3F;
			Data += 2;
		}

		return Result;
	}

	template<>
	inline Elysium::Core::Template::Text::String<char> Encoding::ToASCIIString(const Elysium::Core::Template::Text::String<char32_t>& Input)
	{
		const System::size RequiredLength = Input.GetLength();
		System::byte* Data = (System::byte*)&Input[0];
		String<char> Result = String<char>(RequiredLength);
		Elysium::Core::Template::System::uint32_t IntegerRepresentation;
		for (System::size i = 0; i < RequiredLength; i++)
		{
			IntegerRepresentation = Input[i];
			Result[i] = IntegerRepresentation < 0x80 ? static_cast<char>(IntegerRepresentation) : 0x3F;
			Data += 4;
		}

		return Result;
	}

	template<>
	inline Elysium::Core::Template::Text::String<char> Encoding::ToASCIIString(const Elysium::Core::Template::Text::String<wchar_t>& Input)
	{
		const System::size RequiredLength = Input.GetLength();
		System::byte* Data = (System::byte*)&Input[0];
		Elysium::Core::Template::System::uint16_t IntegerRepresentation;
		String<char> Result = String<char>(RequiredLength);
		for (System::size i = 0; i < RequiredLength; i++)
		{
			IntegerRepresentation = Input[i];
			Result[i] = IntegerRepresentation < 0x80 ? static_cast<char>(IntegerRepresentation) : 0x3F;
			Data += 2;
		}

		return Result;
	}
}
#endif
