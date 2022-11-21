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

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
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
		constexpr UnicodeRange(ConstCharacter FirstCharacter, ConstCharacter LastCharacter) noexcept;

		constexpr UnicodeRange(const UnicodeRange& Source) = delete;

		constexpr UnicodeRange(UnicodeRange&& Right) noexcept = delete;

		constexpr ~UnicodeRange();
	public:
		UnicodeRange& operator=(const UnicodeRange& Source) = delete;

		UnicodeRange& operator=(UnicodeRange&& Right) noexcept = delete;
	public:
		constexpr const System::uint32_t GetFirstCodePoint() const;

		constexpr const System::uint32_t GetLength() const;
	private:
		ConstCharacter _FirstCharacter;
		ConstCharacter _LastCharacter;
	};

	template<Concepts::UnicodeCharacter UC>
	inline constexpr UnicodeRange<UC>::UnicodeRange(ConstCharacter FirstCharacter, ConstCharacter LastCharacter) noexcept
		: _FirstCharacter(FirstCharacter), _LastCharacter(LastCharacter)
	{ }

	template<Concepts::UnicodeCharacter UC>
	inline constexpr UnicodeRange<UC>::~UnicodeRange() noexcept
	{ }

	template<Concepts::UnicodeCharacter UC>
	constexpr const System::uint32_t UnicodeRange<UC>::GetFirstCodePoint() const
	{
		return CharacterTraits<UC>::ConvertToUtf32(&_FirstCharacter);
	}

	template<Concepts::UnicodeCharacter UC>
	constexpr const System::uint32_t UnicodeRange<UC>::GetLength() const
	{
		return _LastCharacter - _FirstCharacter;
	}
}
#endif
