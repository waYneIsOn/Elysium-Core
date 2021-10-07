/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CHARACTERTRAITS
#define ELYSIUM_CORE_TEMPLATE_TEXT_CHARACTERTRAITS

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Template::Text
{
	/// <summary>
	/// 
	/// </summary>
	template <class Character, class Integer>
	struct CharacterTraitsUtility
	{
	public:
		using ConstCharacter = const Character;
		using ConstPointer = const Character*;
	public:
		/// <summary>
		/// Returns the number of bytes required to represent a single character.
		/// </summary>
		static constexpr const unsigned char SizePerCharacter = sizeof(Character);

		/// <summary>
		/// Returns '\0' as specified character-type.
		/// </summary>
		static constexpr ConstCharacter NullTerminationCharacter = Character();

		/// <summary>
		/// 
		/// </summary>
		/// <param name="First"></param>
		/// <returns></returns>
		static constexpr const bool GetIsNull(ConstPointer First);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="First"></param>
		/// <returns></returns>
		static constexpr const bool GetIsEmpty(ConstPointer First);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="First"></param>
		/// <returns></returns>
		static constexpr const bool GetIsNullOrEmpty(ConstPointer First);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="First"></param>
		/// <returns></returns>
		static constexpr const size_t GetLength(ConstPointer First);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="First"></param>
		/// <returns></returns>
		static constexpr const size_t GetByteLength(ConstPointer First);
	};

	template<class CharacterType, class IntegerType>
	inline constexpr const bool CharacterTraitsUtility<CharacterType, IntegerType>::GetIsNull(ConstPointer First)
	{
		return First == nullptr;
	}

	template<class CharacterType, class IntegerType>
	inline constexpr const bool CharacterTraitsUtility<CharacterType, IntegerType>::GetIsEmpty(ConstPointer First)
	{
		if (First == nullptr)
		{
			return false;
		}

		return *First == NullTerminationCharacter;
	}

	template<class CharacterType, class IntegerType>
	inline constexpr const bool CharacterTraitsUtility<CharacterType, IntegerType>::GetIsNullOrEmpty(ConstPointer First)
	{
		if (First == nullptr)
		{
			return true;
		}

		return *First == NullTerminationCharacter;
	}

	template<class CharacterType, class IntegerType>
	inline constexpr const size_t CharacterTraitsUtility<CharacterType, IntegerType>::GetLength(ConstPointer First)
	{
		if (First == nullptr)
		{
			return 0;
		}

		size_t Length = 0;
		while (*First != NullTerminationCharacter)
		{
			Length++;
			First++;
		}

		return Length;
	}

	template<class Character, class Integer>
	inline constexpr const size_t CharacterTraitsUtility<Character, Integer>::GetByteLength(ConstPointer First)
	{
		return GetLength(First) * SizePerCharacter;
	}

	template <class CharacterType>
	struct CharacterTraits
	{ };

	template <>
	struct CharacterTraits<char> : public CharacterTraitsUtility<char, unsigned char>
	{ };

	template <>
	struct CharacterTraits<signed char> : public CharacterTraitsUtility<signed char, signed char>
	{ };

	template <>
	struct CharacterTraits<unsigned char> : public CharacterTraitsUtility<unsigned char, unsigned char>
	{ };

	template <>
	struct CharacterTraits<wchar_t> : public CharacterTraitsUtility<wchar_t, unsigned short>
	{ };

	template <>
	struct CharacterTraits<char8_t> : public CharacterTraitsUtility<char8_t, unsigned char>
	{ };

	template <>
	struct CharacterTraits<char16_t> : public CharacterTraitsUtility<char16_t, unsigned short>
	{ };

	template <>
	struct CharacterTraits<char32_t> : public CharacterTraitsUtility<char32_t, unsigned int>
	{ };
}
#endif
