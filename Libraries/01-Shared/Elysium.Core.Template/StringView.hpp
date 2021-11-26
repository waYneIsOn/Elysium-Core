/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRINGVIEW
#define ELYSIUM_CORE_TEMPLATE_TEXT_STRINGVIEW

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_CHARACTER
#include "Character.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CHARACTERTRAITS
#include "CharacterTraits.hpp"
#endif

namespace Elysium::Core::Template::Text
{
	template <Concepts::Character C>
	class StringViewBase final
	{
	public:
		using ConstCharPointer = const C*;
	public:
		StringViewBase() noexcept;

		StringViewBase(ConstCharPointer Value) noexcept;

		StringViewBase(ConstCharPointer Value, const Elysium::Core::size Size) noexcept;

		StringViewBase(const StringViewBase& Source) = delete;

		StringViewBase(StringViewBase&& Right) noexcept = delete;

		~StringViewBase();
	public:
		StringViewBase<C>& operator=(const StringViewBase& Source) = delete;

		StringViewBase<C>& operator=(StringViewBase&& Right) noexcept = delete;
	private:
		ConstCharPointer _Data;
		Elysium::Core::size _Size;
	};

	template<Concepts::Character C>
	inline StringViewBase<C>::StringViewBase() noexcept
		: StringViewBase<C>(nullptr, 0)
	{ }

	template<Concepts::Character C>
	inline StringViewBase<C>::StringViewBase(ConstCharPointer Value) noexcept
		: StringViewBase<C>(Value, StringTraits<C>::GetLength(Value))
	{ }

	template<Concepts::Character C>
	inline StringViewBase<C>::StringViewBase(ConstCharPointer Value, const Elysium::Core::size Size) noexcept
		: _Data(Value), _Size(Size)
	{ }

	template<Concepts::Character C>
	inline StringViewBase<C>::~StringViewBase()
	{ }

	using StringView = StringViewBase<char>;
	using WideStringView = StringViewBase<wchar_t>;
	using Utf8StringView = StringViewBase<char8_t>;
	using Utf16StringView = StringViewBase<char16_t>;
	using Utf32StringView = StringViewBase<char32_t>;
}
#endif
