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

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CHARACTERTRAITS
#include "CharacterTraits.hpp"
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
		/// <summary>
		/// Indicates whether given text is valid.
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		static constexpr const bool IsValid(ConstPointer Value, Elysium::Core::Template::System::size Length) noexcept;

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

	inline constexpr const bool Elysium::Core::Template::Text::Unicode::Utf8::IsValid(ConstPointer Value, Elysium::Core::Template::System::size Length) noexcept
	{
		if (nullptr == Value || 0 == Length)
		{
			return true;
		}

		char32_t CodePoint;
		Type Buffer[CharacterTraits<Type>::MaximumByteLength] = { 0 };
		System::uint8_t ByteCount;
		for (System::size i = 0; i < Length; ++i)
		{
			CodePoint = CharacterTraits<Type>::ConvertToUtf32(&Value[i]);

			// validate byte count (will also validate lead-byte)
			ByteCount = CharacterTraits<Type>::GetByteCount(Value[i]);
			if (ByteCount == CharacterTraits<Type>::InvalidByteCount || ByteCount > Length)
			{
				return false;
			}

			// validate trail bytes
			for (System::size j = 0; j < ByteCount - 1; j++)
			{
				if (!CharacterTraits<Type>::IsTrailByte(Value[++i]))
				{
					return false;
				}
			}

			// validate code points
			if (CodePoint > 0x10FFFF)
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

}
#endif
