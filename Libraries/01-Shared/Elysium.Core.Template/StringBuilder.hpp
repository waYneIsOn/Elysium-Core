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
	class StringBuilder final
	{
	public:
		using ConstCharacter = const C;
		using CharacterPointer = C*;
		using ConstCharacterPointer = const C*;
		using CharacterReference = C&;
		using ConstCharacterReference = const C&;

		using CorrespondingString = String<C>;
	public:
		StringBuilder() noexcept;

		StringBuilder(const Elysium::Core::Template::System::size Capacity) noexcept;

		StringBuilder(ConstCharacterPointer Value) noexcept;

		StringBuilder(ConstCharacterPointer Value, const Elysium::Core::Template::System::size Length) noexcept;

		StringBuilder(ConstCharacterPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::size Capacity) noexcept;

		StringBuilder(const StringBuilder& Source) = delete;

		StringBuilder(StringBuilder&& Right) noexcept = delete;

		~StringBuilder();
	public:
		StringBuilder<C, Allocator>& operator=(const StringBuilder& Source) = delete;

		StringBuilder<C, Allocator>& operator=(StringBuilder&& Right) noexcept = delete;
	private:
		static const Elysium::Core::Template::System::size DefaultCapacity = 16;
	public:
		//const Elysium::Core::Template::System::size& GetCapacity() const;
		
		//const Elysium::Core::Template::System::size& GetLength() const;
	public:
		StringBuilder<C, Allocator>& Append(ConstCharacter Value);

		StringBuilder<C, Allocator>& Append(ConstCharacterPointer Value);
		
		StringBuilder<C, Allocator>& Append(ConstCharacterPointer Value, const Elysium::Core::Template::System::size Length);

		StringBuilder<C, Allocator>& AppendLine();

		StringBuilder<C, Allocator>& AppendLine(ConstCharacterPointer Value, const Elysium::Core::Template::System::size Length);

		void Clear();

		StringBuilder<C, Allocator>::CorrespondingString ToString() const;
	private:
		inline static Allocator _Allocator = Allocator();
	private:
		CharacterPointer _Data;	// while .NET uses a linked list, this is mostly due to strings being immutable, which isn't the case in this framework
		System::size _Length;
		System::size _Capacity;
	};

	template<Concepts::Character C, class Allocator>
	inline StringBuilder<C, Allocator>::StringBuilder() noexcept
		: StringBuilder(nullptr, 0, DefaultCapacity)
	{ }

	template<Concepts::Character C, class Allocator>
	inline StringBuilder<C, Allocator>::StringBuilder(const Elysium::Core::Template::System::size Capacity) noexcept
		: StringBuilder(nullptr, 0, Capacity)
	{ }

	template<Concepts::Character C, class Allocator>
	inline StringBuilder<C, Allocator>::StringBuilder(ConstCharacterPointer Value) noexcept
		: StringBuilder(Value, CharacterTraits<C>::GetLength(Value), CharacterTraits<C>::GetLength(Value))
	{ }

	template<Concepts::Character C, class Allocator>
	inline StringBuilder<C, Allocator>::StringBuilder(ConstCharacterPointer Value, const Elysium::Core::Template::System::size Length) noexcept
		: StringBuilder(Value, Length, Length)
	{ }

	template<Concepts::Character C, class Allocator>
	inline StringBuilder<C, Allocator>::StringBuilder(ConstCharacterPointer Value, const Elysium::Core::Template::System::size Length, const Elysium::Core::Template::System::size Capacity) noexcept
		 : _Data(_Allocator.Allocate(Capacity)), _Length(Length > Capacity ? Capacity : Length), _Capacity(Capacity)
	{
		CharacterTraits<C>::Copy(_Data, Value, _Length);
	}

	template<Concepts::Character C, class Allocator>
	inline StringBuilder<C, Allocator>::~StringBuilder()
	{
		_Allocator.Deallocate(_Data, _Capacity);
		_Data = nullptr;
		_Length = 0;
		_Capacity = 0;
	}

	template<Concepts::Character C, class Allocator>
	inline StringBuilder<C, Allocator>& StringBuilder<C, Allocator>::Append(ConstCharacter Value)
	{
		return Append(&Value, 1);
	}

	template<Concepts::Character C, class Allocator>
	inline StringBuilder<C, Allocator>& StringBuilder<C, Allocator>::Append(ConstCharacterPointer Value)
	{
		return Append(Value, CharacterTraits<C>::GetLength(Value));
	}

	template<Concepts::Character C, class Allocator>
	inline StringBuilder<C, Allocator>& StringBuilder<C, Allocator>::Append(ConstCharacterPointer Value, const Elysium::Core::Template::System::size Length)
	{
		if (Value == nullptr || Length == 0)
		{
			return *this;
		}

		// resize if required
		const Elysium::Core::Template::System::size DesiredLength = _Length + Length;
		if (DesiredLength > _Capacity)
		{
			Elysium::Core::Template::System::size CalculatedCapacity = 0;
			do
			{
				CalculatedCapacity = CalculatedCapacity * 2 + 1;
			} while (CalculatedCapacity < DesiredLength);

			CharacterPointer OldData = _Data;
			_Data = _Allocator.Allocate(CalculatedCapacity);
			CharacterTraits<C>::Copy(_Data, OldData, _Length);
			_Allocator.Deallocate(OldData, _Capacity);
			_Capacity = CalculatedCapacity;
		}

		// ...
		CharacterTraits<C>::Copy(&_Data[_Length], Value, Length);
		_Length += Length;

		return *this;
	}

	template<Concepts::Character C, class Allocator>
	inline StringBuilder<C, Allocator>& StringBuilder<C, Allocator>::AppendLine()
	{
		return Append(CharacterTraits<C>::NewLineCharacters);
	}

	template<Concepts::Character C, class Allocator>
	inline StringBuilder<C, Allocator>& StringBuilder<C, Allocator>::AppendLine(ConstCharacterPointer Value, const Elysium::Core::Template::System::size Length)
	{
		Append(Value, Length);
		return Append(CharacterTraits<C>::NewLineCharacters);
	}
	
	template<Concepts::Character C, class Allocator>
	inline void StringBuilder<C, Allocator>::Clear()
	{
		_Length = 0;
	}

	template<Concepts::Character C, class Allocator>
	inline StringBuilder<C, Allocator>::CorrespondingString StringBuilder<C, Allocator>::ToString() const
	{
		return CorrespondingString(_Data, _Length);
	}
}
#endif
