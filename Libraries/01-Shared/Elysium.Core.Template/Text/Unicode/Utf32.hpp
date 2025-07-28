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
		inline static constexpr const Type ByteOrderMarkLittleEndian[] = { 0x00, 0x00, 0xFE, 0xFF };

		inline static constexpr const Type ByteOrderMarkBigEndian[] = { 0xFF, 0xFE, 0x00, 0x00 };
	/*
	public:
		/// <summary>
		/// Indicates whether given utf-8 is valid.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsValid(ConstPointer Value, Elysium::Core::Template::System::size Length) noexcept;
	public:
		/// <summary>
		/// Returns the unicode code point representation.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const char32_t ConvertToUtf32(ConstPointer Value) noexcept;
	*/
	};
}
#endif
