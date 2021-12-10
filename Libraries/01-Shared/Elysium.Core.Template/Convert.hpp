/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CONVERT
#define ELYSIUM_CORE_TEMPLATE_TEXT_CONVERT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_CHARACTER
#include "Character.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NUMERIC_NUMERICLIMITS
#include "NumericLimits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CHARACTERTRAITS
#include "CharacterTraits.hpp"
#endif

namespace Elysium::Core::Template::Text
{
	template <Concepts::Character C>
	struct Convert
	{
	public:
		using Value = C;
		using Pointer = C*;
		using ConstValue = const C;
		using ConstPointer = const C*;
		using ConstReference = const C&;
	public:
		static Elysium::Core::int32_t ToInt32(ConstPointer Value, const Elysium::Core::size Length, const Elysium::Core::uint8_t FromBase);
	private:
		static const Elysium::Core::int32_t ToInt32FromBase10(ConstPointer Value, const Elysium::Core::size Length);

		static const Elysium::Core::int32_t ToInt32FromBase16(ConstPointer Value, const Elysium::Core::size Length);
	};

	template<Concepts::Character C>
	inline Elysium::Core::int32_t Convert<C>::ToInt32(ConstPointer Value, const Elysium::Core::size Length, const Elysium::Core::uint8_t FromBase)
	{
		switch (FromBase)
		{
		case 10:
			return ToInt32FromBase10(Value, Length);
		case 16:
			return ToInt32FromBase16(Value, Length);
		default:
			throw NotImplementedException();
		}
	}

	template<Concepts::Character C>
	inline const Elysium::Core::int32_t Convert<C>::ToInt32FromBase10(ConstPointer Value, const Elysium::Core::size Length)
	{
		// taken from: https://www.geeksforgeeks.org/write-your-own-atoi/
		Elysium::Core::int16_t Sign = 1;
		Elysium::Core::int32_t i = 0;
		Elysium::Core::int32_t Base = 0;
		
		// eat all whitespaces
		while (Value[i] == CharacterTraits<C>::WhitespaceCharacter)
		{
			i++;
		}

		// sign
		if (Value[i] == CharacterTraits<C>::MinusCharacter || Value[i] == CharacterTraits<C>::PlusCharacter)
		{
			Sign = 1 - 2 * (Value[i++] == CharacterTraits<C>::MinusCharacter);
		}

		// ...
		while (Value[i] >= static_cast<ConstValue>('0') && Value[i] <= static_cast<ConstValue>('9') && i < Length)
		{
			// handle overflow cases
			if (Base > Elysium::Core::Template::Numeric::NumericLimits<Elysium::Core::int32_t>::Maximum / 10 ||
				(Base == Elysium::Core::Template::Numeric::NumericLimits<Elysium::Core::int32_t>::Maximum / 10 && Value[i] - static_cast<ConstValue>('0') > 7))
			{
				return Sign == 1 ? Elysium::Core::Template::Numeric::NumericLimits<Elysium::Core::int32_t>::Maximum :
					Elysium::Core::Template::Numeric::NumericLimits<Elysium::Core::int32_t>::Minimum;
			}

			Base = 10 * Base + (Value[i++] - static_cast<ConstValue>('0'));
		}

		return Base * Sign;
	}

	template<Concepts::Character C>
	inline const Elysium::Core::int32_t Convert<C>::ToInt32FromBase16(ConstPointer Value, const Elysium::Core::size Length)
	{
		Elysium::Core::int16_t Sign = 1;
		Elysium::Core::int32_t i = 0;
		Elysium::Core::int32_t Base = 0;

		// eat all whitespaces
		while (Value[i] == CharacterTraits<C>::WhitespaceCharacter)
		{
			i++;
		}

		// sign
		if (Value[i] == CharacterTraits<C>::MinusCharacter || Value[i] == CharacterTraits<C>::PlusCharacter)
		{
			Sign = 1 - 2 * (Value[i++] == CharacterTraits<C>::MinusCharacter);
		}

		// ...
		while (true)
		{
			if (Value[i] >= static_cast<ConstValue>('0') && Value[i] <= static_cast<ConstValue>('9') && i < Length)
			{
				Base = 16 * Base + (Value[i++] - static_cast<ConstValue>('0'));
			}
			else if (Value[i] >= static_cast<ConstValue>('a') && Value[i] <= static_cast<ConstValue>('f') && i < Length)
			{
				Base = 16 * Base + (Value[i++] - static_cast<ConstValue>('a'));
			}
			else if (Value[i] >= static_cast<ConstValue>('A') && Value[i] <= static_cast<ConstValue>('F') && i < Length)
			{
				Base = 16 * Base + (Value[i++] - static_cast<ConstValue>('A'));
			}
			else
			{
				break;
			}
		}

		return Base * Sign;
	}
}
#endif
