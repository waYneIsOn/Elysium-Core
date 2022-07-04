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
	template <Concepts::Character C, class Allocator = Memory::DefaultAllocator<C>>
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

		StringBuilderBase(ConstCharacterPointer Value) noexcept;

		StringBuilderBase(ConstCharacterPointer Value, const Elysium::Core::Template::System::size Length) noexcept;

		StringBuilderBase(ConstCharacterPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::size Capacity) noexcept;

		StringBuilderBase(const StringBuilderBase& Source) = delete;

		StringBuilderBase(StringBuilderBase&& Right) noexcept = delete;

		~StringBuilderBase();
	public:
		StringBuilderBase<C, Allocator>& operator=(const StringBuilderBase& Source) = delete;

		StringBuilderBase<C, Allocator>& operator=(StringBuilderBase&& Right) noexcept = delete;
	private:
		static const Elysium::Core::Template::System::size DefaultCapacity = 16;
	public:
		//const Elysium::Core::Template::System::size& GetCapacity() const;
		
		//const Elysium::Core::Template::System::size& GetLength() const;
	public:
		StringBuilderBase<C, Allocator>& Append(ConstCharacter Value);

		StringBuilderBase<C, Allocator>& Append(ConstCharacterPointer Value);
		
		StringBuilderBase<C, Allocator>& Append(ConstCharacterPointer Value, const Elysium::Core::Template::System::size Length);

		StringBuilderBase<C, Allocator>& AppendLine();

		StringBuilderBase<C, Allocator>& AppendLine(ConstCharacterPointer Value, const Elysium::Core::Template::System::size Length);

		void Clear();

		StringBuilderBase<C, Allocator>::CorrespondingString ToString() const;
	private:
		inline static Allocator _Allocator = Allocator();
	private:
		CharacterPointer _Data;	// while .NET uses a linked list, this is mostly due to strings being immutable, which isn't the case in this framework
		System::size _Length;
		System::size _Capacity;
	};

	template<Concepts::Character C, class Allocator>
	inline StringBuilderBase<C, Allocator>::StringBuilderBase() noexcept
		: StringBuilderBase(nullptr, 0, DefaultCapacity)
	{ }

	template<Concepts::Character C, class Allocator>
	inline StringBuilderBase<C, Allocator>::StringBuilderBase(const Elysium::Core::Template::System::size Capacity) noexcept
		: StringBuilderBase(nullptr, 0, Capacity)
	{ }

	template<Concepts::Character C, class Allocator>
	inline StringBuilderBase<C, Allocator>::StringBuilderBase(ConstCharacterPointer Value) noexcept
		: StringBuilderBase(Value, CharacterTraits<C>::GetLength(Value), CharacterTraits<C>::GetLength(Value))
	{ }

	template<Concepts::Character C, class Allocator>
	inline StringBuilderBase<C, Allocator>::StringBuilderBase(ConstCharacterPointer Value, const Elysium::Core::Template::System::size Length) noexcept
		: StringBuilderBase(Value, Length, Length)
	{ }

	template<Concepts::Character C, class Allocator>
	inline StringBuilderBase<C, Allocator>::StringBuilderBase(ConstCharacterPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::size Capacity) noexcept
		 : _Data(_Allocator.Allocate(Capacity)), _Length(Length > Capacity ? Capacity : Length), _Capacity(Capacity)
	{
		memcpy(&_Data[0], Value, _Length * CharacterTraits<C>::MinimumValue);
	}

	template<Concepts::Character C, class Allocator>
	inline StringBuilderBase<C, Allocator>::~StringBuilderBase()
	{
		_Allocator.Deallocate(_Data, 0);
		_Data = nullptr;
	}

	template<Concepts::Character C, class Allocator>
	inline StringBuilderBase<C, Allocator>& StringBuilderBase<C, Allocator>::Append(ConstCharacter Value)
	{
		return Append(&Value, 1);
	}

	template<Concepts::Character C, class Allocator>
	inline StringBuilderBase<C, Allocator>& StringBuilderBase<C, Allocator>::Append(ConstCharacterPointer Value)
	{
		return Append(Value, CharacterTraits<C>::GetLength(Value));
	}

	template<Concepts::Character C, class Allocator>
	inline StringBuilderBase<C, Allocator>& StringBuilderBase<C, Allocator>::Append(ConstCharacterPointer Value, const Elysium::Core::Template::System::size Length)
	{
		if (Value == nullptr || Length == 0)
		{
			return *this;
		}

		// resize if required
		if (_Length + Length > _Capacity)
		{

		}

		/*
		memcpy(&_Data[_Length], Value, Length * CharacterTraits<C>::MinimumValue);
		_Length += Length;
		*/
		return *this;
	}

	template<Concepts::Character C, class Allocator>
	inline StringBuilderBase<C, Allocator>& StringBuilderBase<C, Allocator>::AppendLine()
	{
		return Append(CharacterTraits<C>::NewLineCharacters);
	}

	template<Concepts::Character C, class Allocator>
	inline StringBuilderBase<C, Allocator>& StringBuilderBase<C, Allocator>::AppendLine(ConstCharacterPointer Value, const Elysium::Core::Template::System::size Length)
	{
		Append(Value, Length);
		return Append(CharacterTraits<C>::NewLineCharacters);
	}
	
	template<Concepts::Character C, class Allocator>
	inline void StringBuilderBase<C, Allocator>::Clear()
	{
		_Length = 0;
	}

	template<Concepts::Character C, class Allocator>
	inline StringBuilderBase<C, Allocator>::CorrespondingString StringBuilderBase<C, Allocator>::ToString() const
	{
		return CorrespondingString(_Data);
	}
}
#endif
