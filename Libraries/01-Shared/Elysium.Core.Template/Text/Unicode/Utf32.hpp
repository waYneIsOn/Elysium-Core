/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UTF32
#define ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UTF32

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CHARACTERTRAITS
#include "CharacterTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UNICODERANGES
#include "../../UnicodeRanges.hpp"
#endif

namespace Elysium::Core::Template::Text::Unicode
{
	class Utf32 final
	{
	public:
		using Type = char32_t;
		using Pointer = char32_t*;
		using ConstType = const char32_t;
		using ConstPointer = const char32_t*;
		using ConstReference = const char32_t&;
	public:
		constexpr Utf32() noexcept = delete;

		constexpr Utf32(const Utf32& Source) = delete;

		constexpr Utf32(Utf32&& Right) noexcept = delete;

		constexpr ~Utf32() = delete;
	public:
		Utf32& operator=(const Utf32& Source) = delete;

		Utf32& operator=(Utf32&& Right) noexcept = delete;
	public:
		inline static constexpr const Type ByteOrderMarkLittleEndian[] = { 0xFF, 0xFE, 0x00, 0x00 };

		inline static constexpr const Type ByteOrderMarkBigEndian[] = { 0x00, 0x00, 0xFE, 0xFF };
	public:
		/// <summary>
		/// Returns whether given text is valid utf-32.
		/// (Make sure to use correct byte-order when calling this method!)
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsValid(ConstPointer Value, Elysium::Core::Template::System::size Length) noexcept;
	};

	inline constexpr const bool Elysium::Core::Template::Text::Unicode::Utf32::IsValid(ConstPointer Value, Elysium::Core::Template::System::size Length) noexcept
	{
		if (nullptr == Value || 0 == Length)
		{
			return true;
		}
		
		for (System::size i = 0; i < Length; ++i)
		{
			if (Value[i] > UnicodeRanges<Type>::All._LastCodePoint || 
				(Value[i] >= CharacterTraits<char16_t>::HighSurrogateLimits[0] && Value[i] <= CharacterTraits<char16_t>::LowSurrogateLimits[1])
			)
			{
				return false;
			}
		}

		return true;
	}
}
#endif
