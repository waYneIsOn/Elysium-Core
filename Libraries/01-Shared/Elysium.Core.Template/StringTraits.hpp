/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRINGTRAITS
#define ELYSIUM_CORE_TEMPLATE_TEXT_STRINGTRAITS

#ifdef _MSC_VER
#pragma once
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
	struct StringTraitsBase
	{
	public:
		using ConstCharacter = const C;
		using ConstCharacterPointer = const C*;
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="First"></param>
		/// <returns></returns>
		static constexpr const bool IsNull(ConstCharacterPointer First) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="First"></param>
		/// <returns></returns>
		static constexpr const bool IsEmpty(ConstCharacterPointer First) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="First"></param>
		/// <returns></returns>
		static constexpr const bool IsNullOrEmpty(ConstCharacterPointer First) noexcept;

		/// <summary>
		/// Returns the number of characters in given string up until the first null-termination character.
		/// </summary>
		/// <param name="First"></param>
		/// <returns></returns>
		static constexpr const Elysium::Core::size GetLength(ConstCharacterPointer First) noexcept;

		/// <summary>
		/// Returns the number of bytes in given string up until the first null-termination character.
		/// </summary>
		/// <param name="First"></param>
		/// <returns></returns>
		static constexpr const Elysium::Core::size GetSize(ConstCharacterPointer First) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="First"></param>
		/// <param name="OtherFirst"></param>
		/// <param name="Count"></param>
		/// <returns></returns>
		static constexpr const int Compare(ConstCharacterPointer First, ConstCharacterPointer OtherFirst, const Elysium::Core::size Count) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="First"></param>
		/// <param name="Count"></param>
		/// <param name="Length"></param>
		/// <returns></returns>
		static constexpr ConstCharacterPointer Find(ConstCharacterPointer First, const Elysium::Core::size Count, ConstCharacter Value) noexcept;
	};

	template<Concepts::Character Character>
	inline constexpr const bool StringTraitsBase<Character>::IsNull(ConstCharacterPointer First) noexcept
	{
		return First == nullptr;
	}

	template<Concepts::Character Character>
	inline constexpr const bool StringTraitsBase<Character>::IsEmpty(ConstCharacterPointer First) noexcept
	{
		return First == nullptr ? false : *First == Elysium::Core::Template::Text::CharacterTraits<Character>::NullTerminationCharacter;
	}

	template<Concepts::Character Character>
	inline constexpr const bool StringTraitsBase<Character>::IsNullOrEmpty(ConstCharacterPointer First) noexcept
	{
		return First == nullptr ? true : *First == Elysium::Core::Template::Text::CharacterTraits<Character>::NullTerminationCharacter;
	}

	template<Concepts::Character Character>
	inline constexpr const Elysium::Core::size StringTraitsBase<Character>::GetLength(ConstCharacterPointer First) noexcept
	{
		if (First == nullptr)
		{
			return 0;
		}

		Elysium::Core::size Length = 0;
		while (*First != Elysium::Core::Template::Text::CharacterTraits<Character>::NullTerminationCharacter)
		{
			Length++;
			First++;
		}

		return Length;
	}

	template<Concepts::Character Character>
	inline constexpr const Elysium::Core::size StringTraitsBase<Character>::GetSize(ConstCharacterPointer First) noexcept
	{
		return GetLength(First) * Elysium::Core::Template::Text::CharacterTraits<Character>::MinimumByteLength;
	}

	template<Concepts::Character Character>
	inline constexpr const int StringTraitsBase<Character>::Compare(ConstCharacterPointer First, ConstCharacterPointer OtherFirst, const Elysium::Core::size Count) noexcept
	{
		return __builtin_memcmp(First, OtherFirst, Count);
	}

	template<Concepts::Character Character>
	inline constexpr typename StringTraitsBase<Character>::ConstCharacterPointer StringTraitsBase<Character>::Find(ConstCharacterPointer First, const Elysium::Core::size Count, ConstCharacter Value) noexcept
	{
		return __builtin_char_memchr(First, Value, Count);
	}

	template <>
	inline constexpr StringTraitsBase<char8_t>::ConstCharacterPointer StringTraitsBase<char8_t>::Find(ConstCharacterPointer First, const Elysium::Core::size Count, ConstCharacter Value) noexcept
	{
		Elysium::Core::size CopiedCount = Count;
		for (; 0 < CopiedCount; --CopiedCount, ++First)
		{
			if (*First == Value)
			{
				return First;
			}
		}

		return nullptr;
	}

	template <Concepts::Character C>
	struct StringTraits
	{ };

	template <>
	struct StringTraits<char> : public StringTraitsBase<char>
	{ };

	template <>
	struct StringTraits<signed char> : public StringTraitsBase<signed char>
	{ };

	template <>
	struct StringTraits<unsigned char> : public StringTraitsBase<unsigned char>
	{ };

	template <>
	struct StringTraits<wchar_t> : public StringTraitsBase<wchar_t>
	{ };

	template <>
	struct StringTraits<char8_t> : public StringTraitsBase<char8_t>
	{ };

	template <>
	struct StringTraits<char16_t> : public StringTraitsBase<char16_t>
	{ };

	template <>
	struct StringTraits<char32_t> : public StringTraitsBase<char32_t>
	{ };
}
#endif
