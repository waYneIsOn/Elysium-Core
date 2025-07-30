/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UTF8
#define ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UTF8

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_LITERALS
#include "Literals.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CHARACTERTRAITS
#include "CharacterTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UNICODERANGES
#include "UnicodeRanges.hpp"
#endif

namespace Elysium::Core::Template::Text::Unicode
{
	class Utf8 final
	{
	public:
		using Type = char8_t;
		using Pointer = char8_t*;
		using ConstType = const char8_t;
		using ConstPointer = const char8_t*;
		using ConstReference = const char8_t&;
	public:
		constexpr Utf8() noexcept = delete;

		constexpr Utf8(const Utf8& Source) = delete;

		constexpr Utf8(Utf8&& Right) noexcept = delete;

		constexpr ~Utf8() = delete;
	public:
		Utf8& operator=(const Utf8& Source) = delete;

		Utf8& operator=(Utf8&& Right) noexcept = delete;
	public:
		inline static constexpr const Type ByteOrderMark[] = { 0xEF, 0xBB, 0xBF, 0x00 };
	public:
		/// <summary>
		/// Returns whether given text is valid utf-8.
		/// </summary>
		/// <param name="Value"></param>
		/// <param name="Length"></param>
		/// <returns></returns>
		static constexpr const bool IsValid(ConstPointer Value, Elysium::Core::Template::System::size Length) noexcept;
	public:
		/// <summary>
		/// Returns the unicode code point representation.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const char32_t ConvertToUtf32(ConstPointer Value) noexcept;
		/*
	public:
		template <Concepts::Character C>
		static constexpr System::size GetRequiredLengthFromSafeUtf8String(const C* Data) noexcept;
	public:
		template <Concepts::Character C>
		static String<C> FromSafeUtf8String(const char8_t* Data, const System::size Length) noexcept;

		template <Concepts::Character C>
		static String<char8_t> SafeToUtf8String(const C* Data, const System::size Length) noexcept;
	public:
		
		template <Concepts::Character C>
		static String<C> FromUtf8String(const char8_t* Data, const System::size Length) noexcept;

		template <Concepts::Character C>
		static String<char8_t> ToUtf8String(const C* Data, const System::size Length) noexcept;
		*/
	private:
		static constexpr const char32_t ConvertToUtf32(ConstPointer Value, const Elysium::Core::Template::System::uint8_t ByteCount) noexcept;
	};

	inline constexpr const bool Elysium::Core::Template::Text::Unicode::Utf8::IsValid(ConstPointer Value, Elysium::Core::Template::System::size Length) noexcept
	{
		if (nullptr == Value || 0 == Length)
		{
			return true;
		}

		System::uint8_t ByteCount;
		char32_t CodePoint;
		for (System::size i = 0; i < Length; ++i)
		{
			ByteCount = CharacterTraits<Type>::GetByteCount(Value[i]);

			CodePoint = Utf8::ConvertToUtf32(&Value[i], ByteCount);

			// validate byte count (will also validate lead-byte)
			if (ByteCount == CharacterTraits<Type>::InvalidByteCount || ByteCount > Length)
			{
				return false;
			}

			// validate trail bytes
			for (System::size j = 0; j < ByteCount - 1; j++)
			{
				if (++i > Length || !CharacterTraits<Type>::IsTrailByte(Value[i]))
				{
					return false;
				}
			}

			// validate code points
			if (CodePoint > UnicodeRanges<Type>::All._LastCodePoint)
			{
				return false;
			}

			// check for overlong representation
			if (CodePoint <= 0x7F && ByteCount != 1)
			{
				return false;
			}
			else if (CodePoint > 0x7F && CodePoint <= 0x7FF && ByteCount != 2)
			{
				return false;
			}
			else if (CodePoint > 0x7FF && CodePoint <= 0xFFFF && ByteCount != 3)
			{
				return false;
			}
			else if (CodePoint > 0xFFFF && CodePoint <= 0x10FFFF && ByteCount != 4)
			{
				return false;
			}
		}

		return true;
	}
	
	inline constexpr const char32_t Elysium::Core::Template::Text::Unicode::Utf8::ConvertToUtf32(ConstPointer Value) noexcept
	{
		const System::uint8_t ByteCount = CharacterTraits<Type>::GetByteCount(*Value);

		return Utf8::ConvertToUtf32(Value, ByteCount);
	}

	inline constexpr const char32_t Elysium::Core::Template::Text::Unicode::Utf8::ConvertToUtf32(ConstPointer Value, const Elysium::Core::Template::System::uint8_t ByteCount) noexcept
	{
		switch (ByteCount)
		{
		case 1_ui8:		// 0xxx xxxx										->	0xxx xxxx
			return static_cast<char32_t>(Value[0]);
		case 2_ui8:		// 110y yyyy	10xx xxxx							->	0000 0yyy	yyxx xxxx
			return char32_t(((Value[0] & 0x1F) << 6) | (Value[1] & 0x3F));
		case 3_ui8:		// 1110 zzzz	10yy yyyy	10xx xxxx				->	zzzz yyyy	yyxx xxxx
			return char32_t(((Value[0] & 0x0F) << 12) | ((Value[1] & 0x3F) << 6) | (Value[2] & 0x3F));
		case 4_ui8:		// 1111 0aaa	10zz zzzz	10yy yyyyy	10xx xxxx	->	000a aazz	zzzz yyyy	yyxx xxxx
			return char32_t(((Value[0] & 0x07) << 18) | ((Value[1] & 0x3F) << 12) | ((Value[2] & 0x3F) << 6) | (Value[3] & 0x3F));
		default:	// 10xx xxxx (trail byte. determination not possible)
			return CharacterTraits<char8_t>::InvalidByteCount;
		}
	}
}
#endif
