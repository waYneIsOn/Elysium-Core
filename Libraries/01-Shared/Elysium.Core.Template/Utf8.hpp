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

namespace Elysium::Core::Template::Text::Unicode
{
	class Utf8 final
	{
	public:
		constexpr Utf8() noexcept = delete;

		constexpr Utf8(const Utf8& Source) = delete;

		constexpr Utf8(Utf8&& Right) noexcept = delete;

		constexpr ~Utf8() = delete;
	public:
		Utf8& operator=(const Utf8& Source) = delete;

		Utf8& operator=(Utf8&& Right) noexcept = delete;
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
	};
}
#endif
