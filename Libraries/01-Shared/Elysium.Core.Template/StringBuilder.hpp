/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRINGBUILDER
#define ELYSIUM_CORE_TEMPLATE_TEXT_STRINGBUILDER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_CHARACTER
#include "Character.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_LINKEDLIST
#include "LinkedList.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_DEFAULTALLOCATOR
#include "DefaultAllocator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CHARACTERTRAITS
#include "CharacterTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "String.hpp"
#endif

namespace Elysium::Core::Template::Text
{
	template <Concepts::Character C>
	class StringBuilderBase
	{
	public:
		using ConstCharacter = const C;
		using CharPointer = C*;
		using ConstCharPointer = const C*;
		using CharReference = C&;
		using ConstCharReference = const C&;

		using CorrespondingString = StringBase<C>;
	public:
		StringBuilderBase() noexcept;

		StringBuilderBase(const Elysium::Core::size Capacity) noexcept;

		StringBuilderBase(ConstCharPointer Value, const Elysium::Core::size Length, const Elysium::Core::size Capacity) noexcept;

		StringBuilderBase(const StringBuilderBase& Source) = delete;

		StringBuilderBase(StringBuilderBase&& Right) noexcept = delete;

		~StringBuilderBase();
	public:
		StringBuilderBase<C>& operator=(const StringBuilderBase& Source) = delete;

		StringBuilderBase<C>& operator=(StringBuilderBase&& Right) noexcept = delete;
	private:
		static const Elysium::Core::size DefaultCapacity = 16;
	public:
		//const Elysium::Core::size GetCapacity() const;
		
		//const Elysium::Core::size GetLength() const;
	public:
		StringBuilderBase<C>& Append(ConstCharPointer Value);
		
		StringBuilderBase<C>& Append(ConstCharPointer Value, const Elysium::Core::size Length);

		StringBuilderBase<C>& AppendLine();

		StringBuilderBase<C>& AppendLine(ConstCharPointer Value, const Elysium::Core::size Length);

		void Clear();

		StringBuilderBase<C>::CorrespondingString ToString() const;
	private:
		//Container::LinkedList<C[255]> _Data;
	};

	template<Concepts::Character C>
	inline StringBuilderBase<C>::StringBuilderBase() noexcept
		: StringBuilderBase(DefaultCapacity)
	{ }

	template<Concepts::Character C>
	inline StringBuilderBase<C>::StringBuilderBase(const Elysium::Core::size Capacity) noexcept
		: StringBuilderBase(nullptr, 0, Capacity)
	{ }

	template<Concepts::Character C>
	inline StringBuilderBase<C>::StringBuilderBase(ConstCharPointer Value, const Elysium::Core::size Length, const Elysium::Core::size Capacity) noexcept
		//: _Data{ 0x00 }
	{ }

	template<Concepts::Character C>
	inline StringBuilderBase<C>::~StringBuilderBase()
	{ }

	template<Concepts::Character C>
	inline StringBuilderBase<C>& StringBuilderBase<C>::Append(ConstCharPointer Value)
	{
		return Append(Value, CharacterTraits<C>::GetLength(Value));
	}

	template<Concepts::Character C>
	inline StringBuilderBase<C>& StringBuilderBase<C>::Append(ConstCharPointer Value, const Elysium::Core::size Length)
	{
		if (Value == nullptr || Length == 0)
		{
			return *this;
		}



		return *this;
	}

	template<Concepts::Character C>
	inline StringBuilderBase<C>& StringBuilderBase<C>::AppendLine()
	{
		return Append(CharacterTraits<C>::NewLineCharacters);
	}

	template<Concepts::Character C>
	inline StringBuilderBase<C>& StringBuilderBase<C>::AppendLine(ConstCharPointer Value, const Elysium::Core::size Length)
	{
		Append(Value, Length);
		return Append(CharacterTraits<C>::NewLineCharacters);
	}
	
	template<Concepts::Character C>
	inline void StringBuilderBase<C>::Clear()
	{
	}

	template<Concepts::Character C>
	inline StringBuilderBase<C>::CorrespondingString StringBuilderBase<C>::ToString() const
	{
		return CorrespondingString();
	}
}
#endif
