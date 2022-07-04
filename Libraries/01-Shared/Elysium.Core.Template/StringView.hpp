/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRINGVIEW
#define ELYSIUM_CORE_TEMPLATE_TEXT_STRINGVIEW

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_CHARACTER
#include "Character.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "Move.hpp"
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
	class StringViewBase final
	{
	public:
		using Character = C;
		using ConstCharacter = const C;
		using CharacterPointer = C*;
		using ConstCharacterPointer = const C*;
		using CharacterReference = C&;
		using ConstCharacterReference = const C&;

		using CorrespondingString = StringBase<C>;
	public:
		StringViewBase() noexcept;

		StringViewBase(const CorrespondingString& Value) noexcept;

		StringViewBase(ConstCharacterPointer Value) noexcept;

		StringViewBase(ConstCharacterPointer Value, const System::size Length) noexcept;

		StringViewBase(const StringViewBase& Source);

		StringViewBase(StringViewBase&& Right) noexcept;

		~StringViewBase();
	public:
		StringViewBase<C>& operator=(const StringViewBase& Source);

		StringViewBase<C>& operator=(StringViewBase&& Right) noexcept;
	public:
		StringViewBase<C>::CharacterReference operator[](const System::size Index);

		StringViewBase<C>::ConstCharacterReference operator[](const System::size Index) const;
	public:
		const bool operator==(const StringViewBase<C>& Other) const noexcept;

		const bool operator!=(const StringViewBase<C>& Other) const noexcept;

		const bool operator<(const StringViewBase<C>& Other) const noexcept;

		const bool operator>(const StringViewBase<C>& Other) const noexcept;

		const bool operator<=(const StringViewBase<C>& Other) const noexcept;

		const bool operator>=(const StringViewBase<C>& Other) const noexcept;
	public:
		static const bool IsNullOrEmtpy(const StringViewBase<C>& Value);
	public:
		const System::size GetLength() const;
	public:
		const System::size IndexOf(ConstCharacter Value) const noexcept;

		const System::size IndexOf(ConstCharacter Value, const System::size StartIndex) const noexcept;

		const System::size IndexOf(ConstCharacterPointer Sequence) const noexcept;

		const System::size IndexOf(ConstCharacterPointer Sequence, const System::size StartIndex) const noexcept;

		const System::size IndexOfAny(ConstCharacterPointer Sequence, const System::size SequenceLength) const noexcept;

		const System::size IndexOfAny(ConstCharacterPointer Sequence, const System::size SequenceLength, const System::size StartIndex) const noexcept;

		const System::size LastIndexOf(ConstCharacter Value) const noexcept;

		const System::size LastIndexOf(ConstCharacterPointer Sequence) const noexcept;

		Container::Vector<StringViewBase<C>> Split(ConstCharacter Delimiter) const;

		Container::Vector<StringViewBase<C>> Split(ConstCharacterPointer DelimiterSequence) const;

		StringViewBase<C> Substringview(const System::size StartIndex, const System::size Length) const;

		StringViewBase<C>::CorrespondingString ToString() const;
	private:
		ConstCharacterPointer _Data;
		System::size _Length;
	};

	template<Concepts::Character C>
	inline StringViewBase<C>::StringViewBase() noexcept
		: StringViewBase<C>(nullptr, 0)
	{ }

	template<Concepts::Character C>
	inline StringViewBase<C>::StringViewBase(const CorrespondingString & Value) noexcept
		: StringViewBase<C>(&Value[0], Value.GetLength())
	{ }

	template<Concepts::Character C>
	inline StringViewBase<C>::StringViewBase(ConstCharacterPointer Value) noexcept
		: StringViewBase<C>(Value, CharacterTraits<C>::GetLength(Value))
	{ }

	template<Concepts::Character C>
	inline StringViewBase<C>::StringViewBase(ConstCharacterPointer Value, const Elysium::Core::Template::System::size Length) noexcept
		: _Data(Value), _Length(Length)
	{ }

	template<Concepts::Character C>
	inline StringViewBase<C>::StringViewBase(const StringViewBase & Source)
		: _Data(Source._Data), _Length(Source._Length)
	{ }

	template<Concepts::Character C>
	inline StringViewBase<C>::StringViewBase(StringViewBase && Right) noexcept
		: _Data(nullptr), _Length(0)
	{
		*this = Elysium::Core::Template::Functional::Move(Right);
	}

	template<Concepts::Character C>
	inline StringViewBase<C>::~StringViewBase()
	{ }

	template<Concepts::Character C>
	inline StringViewBase<C>& StringViewBase<C>::operator=(const StringViewBase & Source)
	{
		if (this != &Source)
		{
			_Length = Source._Length;
			_Data = Source._Data;
		}
		return *this;
	}

	template<Concepts::Character C>
	inline StringViewBase<C>& StringViewBase<C>::operator=(StringViewBase&& Right) noexcept
	{
		if (this != &Right)
		{
			_Data = Elysium::Core::Template::Functional::Move(Right._Data);
			_Length = Elysium::Core::Template::Functional::Move(Right._Length);

			Right._Length = 0;
			Right._Data = nullptr;
		}
		return *this;
	}

	template<Concepts::Character C>
	inline StringViewBase<C>::CharacterReference StringViewBase<C>::operator[](const Elysium::Core::Template::System::size Index)
	{
		if (Index >= _Length)
		{
			//throw IndexOutOfRangeException();
		}

		return (CharacterReference)_Data[Index];
	}

	template<Concepts::Character C>
	inline StringViewBase<C>::ConstCharacterReference StringViewBase<C>::operator[](const Elysium::Core::Template::System::size Index) const
	{
		if (Index >= _Length)
		{
			//throw IndexOutOfRangeException();
		}

		return _Data[Index];
	}

	template<Concepts::Character C>
	inline const bool StringViewBase<C>::operator==(const StringViewBase<C>& Other) const noexcept
	{
		if (this == &Other)
		{
			return true;
		}
		return _Data == Other._Data && _Length == Other._Length;
	}

	template<Concepts::Character C>
	inline const bool StringViewBase<C>::operator!=(const StringViewBase<C>& Other) const noexcept
	{
		if (this == &Other)
		{
			return false;
		}
		return _Data != Other._Data || _Length != Other._Length;
	}

	template<Concepts::Character C>
	inline const bool StringViewBase<C>::operator<(const StringViewBase<C>& Other) const noexcept
	{
		if (this == &Other)
		{
			return false;
		}
		return _Data == Other._Data && _Length < Other._Length;
	}

	template<Concepts::Character C>
	inline const bool StringViewBase<C>::operator>(const StringViewBase<C>& Other) const noexcept
	{
		if (this == &Other)
		{
			return false;
		}
		return _Data == Other._Data && _Length > Other._Length;
	}

	template<Concepts::Character C>
	inline const bool StringViewBase<C>::operator<=(const StringViewBase<C>& Other) const noexcept
	{
		if (this == &Other)
		{
			return true;
		}
		return _Data == Other._Data && _Length <= Other._Length;
	}

	template<Concepts::Character C>
	inline const bool StringViewBase<C>::operator>=(const StringViewBase<C>& Other) const noexcept
	{
		if (this == &Other)
		{
			return true;
		}
		return _Data == Other._Data && _Length >= Other._Length;
	}

	template<Concepts::Character C>
	inline const bool StringViewBase<C>::IsNullOrEmtpy(const StringViewBase<C>& Value)
	{
		return CharacterTraits<C>::IsNullOrEmpty(Value._Data);
	}

	template<Concepts::Character C>
	inline const Elysium::Core::Template::System::size StringViewBase<C>::GetLength() const
	{
		return _Length;
	}

	template<Concepts::Character C>
	inline const Elysium::Core::Template::System::size StringViewBase<C>::IndexOf(ConstCharacter Value) const noexcept
	{
		return CharacterTraits<C>::IndexOf(_Data, _Length, Value);
	}

	template<Concepts::Character C>
	inline const Elysium::Core::Template::System::size StringViewBase<C>::IndexOf(ConstCharacter Value, const Elysium::Core::Template::System::size StartIndex) const noexcept
	{
		return CharacterTraits<C>::IndexOf(&_Data[StartIndex], _Length - StartIndex, Value);
	}

	template<Concepts::Character C>
	inline const Elysium::Core::Template::System::size StringViewBase<C>::IndexOf(ConstCharacterPointer Sequence) const noexcept
	{
		return CharacterTraits<C>::IndexOf(_Data, _Length, Sequence);
	}

	template<Concepts::Character C>
	inline const Elysium::Core::Template::System::size StringViewBase<C>::IndexOf(ConstCharacterPointer Sequence, const Elysium::Core::Template::System::size StartIndex) const noexcept
	{
		return CharacterTraits<C>::IndexOf(&_Data[StartIndex], _Length - StartIndex, Sequence);
	}

	template<Concepts::Character C>
	inline const System::size StringViewBase<C>::IndexOfAny(ConstCharacterPointer Sequence, const System::size SequenceLength) const noexcept
	{
		return CharacterTraits<C>::IndexOfAny(_Data, _Length, Sequence, SequenceLength);
	}

	template<Concepts::Character C>
	inline const System::size StringViewBase<C>::IndexOfAny(ConstCharacterPointer Sequence, const System::size SequenceLength, const System::size StartIndex) const noexcept
	{
		return CharacterTraits<C>::IndexOfAny(&_Data[StartIndex], _Length - StartIndex, Sequence, SequenceLength);
	}

	template<Concepts::Character C>
	inline const Elysium::Core::Template::System::size StringViewBase<C>::LastIndexOf(ConstCharacter Value) const noexcept
	{
		return CharacterTraits<C>::LastIndexOf(_Data, _Length, Value);
	}

	template<Concepts::Character C>
	inline const Elysium::Core::Template::System::size StringViewBase<C>::LastIndexOf(ConstCharacterPointer Sequence) const noexcept
	{
		return CharacterTraits<C>::LastIndexOf(_Data, _Length, Sequence);
	}

	template<Concepts::Character C>
	inline Container::Vector<StringViewBase<C>> StringViewBase<C>::Split(ConstCharacter Delimiter) const
	{
		Container::Vector<StringViewBase<C>> Result = Container::Vector<StringViewBase<C>>();

		Elysium::Core::Template::System::size StartIndex = 0;
		Elysium::Core::Template::System::size Length = 0;

		while (true)
		{
			Length = IndexOf(Delimiter, StartIndex);
			if (Length == static_cast<Elysium::Core::Template::System::size>(-1))
			{
				if (_Length - StartIndex > 0)
				{
					Result.PushBack(Elysium::Core::Template::Functional::Move(StringViewBase<C>(&_Data[StartIndex], _Length - StartIndex)));
				}
				break;
			}
			Result.PushBack(Elysium::Core::Template::Functional::Move(StringViewBase<C>(&_Data[StartIndex], Length)));
			StartIndex += Length + 1;
		}

		return Result;
	}

	template<Concepts::Character C>
	inline Container::Vector<StringViewBase<C>> StringViewBase<C>::Split(ConstCharacterPointer DelimiterSequence) const
	{
		Container::Vector<StringViewBase<C>> Result = Container::Vector<StringViewBase<C>>();

		Elysium::Core::Template::System::size DelimiterLength = Elysium::Core::Template::Text::CharacterTraits<C>::GetLength(DelimiterSequence);
		Elysium::Core::Template::System::size StartIndex = 0;
		Elysium::Core::Template::System::size Length = 0;

		while (true)
		{
			Length = IndexOf(DelimiterSequence, StartIndex);
			if (Length == static_cast<Elysium::Core::Template::System::size>(-1))
			{
				if (_Length - StartIndex > 0)
				{
					Result.PushBack(Elysium::Core::Template::Functional::Move(StringViewBase<C>(&_Data[StartIndex], _Length - StartIndex)));
				}
				break;
			}
			Result.PushBack(Elysium::Core::Template::Functional::Move(StringViewBase<C>(&_Data[StartIndex], Length - StartIndex)));
			StartIndex += (Length - StartIndex) + DelimiterLength;
		}
	
		return Result;
	}

	template<Concepts::Character C>
	inline StringViewBase<C> StringViewBase<C>::Substringview(const Elysium::Core::Template::System::size StartIndex, const Elysium::Core::Template::System::size Length) const
	{
		return StringViewBase<C>(&_Data[StartIndex], Length);
	}

	template<Concepts::Character C>
	inline StringViewBase<C>::CorrespondingString StringViewBase<C>::ToString() const
	{
		return CorrespondingString(_Data, _Length);
	}
}
#endif
