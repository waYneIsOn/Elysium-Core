/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#define ELYSIUM_CORE_TEMPLATE_TEXT_STRING

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_CHARACTER
#include "Character.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_DEFAULTALLOCATOR
#include "DefaultAllocator.hpp"
#endif

namespace Elysium::Core::Template::Text
{
	template <Concepts::Character C, class Allocator = Memory::DefaultAllocator<C>>
	class StringBase
	{
	public:
		using ConstCharacter = const C;
		using Pointer = C*;
		using ConstPointer = const C*;
	public:
		StringBase() noexcept;
		StringBase(ConstPointer Value) noexcept;
		StringBase(const StringBase& Source) = delete;
		StringBase(StringBase&& Right) noexcept = delete;
		~StringBase();

		StringBase<C, Allocator>& operator=(const StringBase& Source) = delete;
		StringBase<C, Allocator>& operator=(StringBase&& Right) noexcept = delete;
		StringBase<C, Allocator>& operator=(ConstPointer Value) = delete;
	private:
		inline static Allocator _Allocator = Allocator();
	private:
		/*
		Elysium::Core::size _Capacity;
		Elysium::Core::size _Size;
		Pointer _Data;
		*/
	};

	template<Concepts::Character C, class Allocator>
	inline StringBase<C, Allocator>::StringBase() noexcept
	{ }

	template<Concepts::Character C, class Allocator>
	inline StringBase<C, Allocator>::StringBase(ConstPointer Value) noexcept
	{ }

	template<Concepts::Character C, class Allocator>
	inline StringBase<C, Allocator>::~StringBase()
	{ }

	using String = StringBase<char>;
	using WideString = StringBase<wchar_t>;
	using Utf8String = StringBase<char8_t>;
	using Utf16String = StringBase<char16_t>;
	using Utf32String = StringBase<char32_t>;
}
#endif
