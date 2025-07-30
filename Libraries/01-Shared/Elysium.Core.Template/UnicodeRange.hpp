/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UNICODERANGE
#define ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UNICODERANGE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_UNICODECHARACTER
#include "UnicodeCharacter.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CHARACTERTRAITS
#include "CharacterTraits.hpp"
#endif

namespace Elysium::Core::Template::Text::Unicode
{
	template <Concepts::UnicodeCharacter UC>
	class UnicodeRange final
	{
	public:
		using ConstCharacter = const UC;
	public:
		constexpr UnicodeRange(const char32_t FirstCodePoint, const char32_t LastCodePoint) noexcept;

		constexpr UnicodeRange(const UnicodeRange& Source) = delete;

		constexpr UnicodeRange(UnicodeRange&& Right) noexcept = delete;

		constexpr ~UnicodeRange() noexcept = default;
	public:
		UnicodeRange& operator=(const UnicodeRange& Source) = delete;

		UnicodeRange& operator=(UnicodeRange&& Right) noexcept = delete;
	public:
		constexpr const char32_t GetLength() const noexcept;
	/*
	public:
		constexpr const ConstCharacter GetFirstCharacter() const;

		constexpr const ConstCharacter GetLastCharacter() const;
	*/
	public:
		const char32_t _FirstCodePoint;
		const char32_t _LastCodePoint;
	};

	template<Concepts::UnicodeCharacter UC>
	inline constexpr UnicodeRange<UC>::UnicodeRange(const char32_t FirstCodePoint, const char32_t LastCodePoint) noexcept
		: _FirstCodePoint(FirstCodePoint), _LastCodePoint(LastCodePoint)
	{ }

	template<Concepts::UnicodeCharacter UC>
	constexpr const char32_t UnicodeRange<UC>::GetLength() const noexcept
	{
		return _LastCodePoint - _FirstCodePoint;
	}
	/*
	template<Concepts::UnicodeCharacter UC>
	inline constexpr const UnicodeRange<UC>::ConstCharacter UnicodeRange<UC>::GetFirstCharacter() const
	{
		return CharacterTraits<UC>::ConvertFromUtf32();
	}

	template<Concepts::UnicodeCharacter UC>
	inline constexpr const UnicodeRange<UC>::ConstCharacter UnicodeRange<UC>::GetLastCharacter() const
	{
		return ConstCharacter();
	}
	*/
}
#endif
