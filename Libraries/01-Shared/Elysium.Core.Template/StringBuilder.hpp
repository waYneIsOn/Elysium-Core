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

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_CHARACTER
#include "Character.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_LINKEDLIST
#include "LinkedList.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_DEFAULTALLOCATOR
#include "DefaultAllocator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
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
	class StringBuilderBase final
	{
	public:
		using ConstCharacter = const C;
		using CharacterPointer = C*;
		using ConstCharacterPointer = const C*;
		using CharacterReference = C&;
		using ConstCharacterReference = const C&;

		using CorrespondingString = StringBase<C>;
	public:
		StringBuilderBase() noexcept;

		StringBuilderBase(const Elysium::Core::Template::System::size Capacity) noexcept;

		StringBuilderBase(ConstCharacterPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::size Capacity) noexcept;

		StringBuilderBase(const StringBuilderBase& Source) = delete;

		StringBuilderBase(StringBuilderBase&& Right) noexcept = delete;

		~StringBuilderBase();
	public:
		StringBuilderBase<C>& operator=(const StringBuilderBase& Source) = delete;

		StringBuilderBase<C>& operator=(StringBuilderBase&& Right) noexcept = delete;
	private:
		static const Elysium::Core::Template::System::size DefaultCapacity = 16;
	public:
		//const Elysium::Core::Template::System::size GetCapacity() const;
		
		//const Elysium::Core::Template::System::size GetLength() const;
	public:
		StringBuilderBase<C>& Append(ConstCharacter Value);

		StringBuilderBase<C>& Append(ConstCharacterPointer Value);
		
		StringBuilderBase<C>& Append(ConstCharacterPointer Value, const Elysium::Core::Template::System::size Length);

		StringBuilderBase<C>& AppendLine();

		StringBuilderBase<C>& AppendLine(ConstCharacterPointer Value, const Elysium::Core::Template::System::size Length);

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
	inline StringBuilderBase<C>::StringBuilderBase(const Elysium::Core::Template::System::size Capacity) noexcept
		: StringBuilderBase(nullptr, 0, Capacity)
	{ }

	template<Concepts::Character C>
	inline StringBuilderBase<C>::StringBuilderBase(ConstCharacterPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::size Capacity) noexcept
		//: _Data{ 0x00 }
	{ }

	template<Concepts::Character C>
	inline StringBuilderBase<C>::~StringBuilderBase()
	{ }

	template<Concepts::Character C>
	inline StringBuilderBase<C>& StringBuilderBase<C>::Append(ConstCharacter Value)
	{
		return Append(&Value, 1);
	}

	template<Concepts::Character C>
	inline StringBuilderBase<C>& StringBuilderBase<C>::Append(ConstCharacterPointer Value)
	{
		return Append(Value, CharacterTraits<C>::GetLength(Value));
	}

	template<Concepts::Character C>
	inline StringBuilderBase<C>& StringBuilderBase<C>::Append(ConstCharacterPointer Value, const Elysium::Core::Template::System::size Length)
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
	inline StringBuilderBase<C>& StringBuilderBase<C>::AppendLine(ConstCharacterPointer Value, const Elysium::Core::Template::System::size Length)
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
