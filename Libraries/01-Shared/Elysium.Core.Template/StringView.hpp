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
	template <Concepts::Character C, class Traits = CharacterTraits<C>>
	class StringView final
	{
	public:
		using Character = C;
		using ConstCharacter = const C;
		using CharacterPointer = C*;
		using ConstCharacterPointer = const C*;
		using CharacterReference = C&;
		using ConstCharacterReference = const C&;

		using CorrespondingString = String<C>;
	public:
		StringView() noexcept;

		StringView(const CorrespondingString& Value) noexcept;

		StringView(ConstCharacterPointer Value) noexcept;

		StringView(ConstCharacterPointer Value, const System::size Length) noexcept;

		StringView(const StringView& Source);

		StringView(StringView&& Right) noexcept;

		~StringView();
	public:
		StringView<C, Traits>& operator=(const StringView& Source);

		StringView<C, Traits>& operator=(StringView&& Right) noexcept;
	public:
		StringView<C, Traits>::CharacterReference operator[](const System::size Index);

		StringView<C, Traits>::ConstCharacterReference operator[](const System::size Index) const;
	public:
		const bool operator==(const StringView& Other) const noexcept;

		const bool operator!=(const StringView& Other) const noexcept;

		const bool operator<(const StringView& Other) const noexcept;

		const bool operator>(const StringView& Other) const noexcept;

		const bool operator<=(const StringView& Other) const noexcept;

		const bool operator>=(const StringView& Other) const noexcept;
	public:
		static const bool IsNullOrEmtpy(const StringView& Value);
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

		Container::Vector<StringView<C, Traits>> Split(ConstCharacter Delimiter) const;

		Container::Vector<StringView<C, Traits>> Split(ConstCharacterPointer DelimiterSequence) const;

		StringView<C, Traits> Substringview(const System::size StartIndex, const System::size Length) const;

		StringView<C, Traits>::CorrespondingString ToString() const;
	private:
		ConstCharacterPointer _Data;
		System::size _Length;
	};

	template<Concepts::Character C, class Traits>
	inline StringView<C, Traits>::StringView() noexcept
		: StringView<C, Traits>(nullptr, 0)
	{ }

	template<Concepts::Character C, class Traits>
	inline StringView<C, Traits>::StringView(const CorrespondingString & Value) noexcept
		: StringView<C, Traits>(Value.GetLength() == 0 ? nullptr : &Value[0], Value.GetLength())
	{ }

	template<Concepts::Character C, class Traits>
	inline StringView<C, Traits>::StringView(ConstCharacterPointer Value) noexcept
		: StringView<C, Traits>(Value, CharacterTraits<C>::GetLength(Value))
	{ }

	template<Concepts::Character C, class Traits>
	inline StringView<C, Traits>::StringView(ConstCharacterPointer Value, const Elysium::Core::Template::System::size Length) noexcept
		: _Data(Value), _Length(Length)
	{ }

	template<Concepts::Character C, class Traits>
	inline StringView<C, Traits>::StringView(const StringView& Source)
		: _Data(Source._Data), _Length(Source._Length)
	{ }

	template<Concepts::Character C, class Traits>
	inline StringView<C, Traits>::StringView(StringView&& Right) noexcept
		: _Data(nullptr), _Length(0)
	{
		*this = Elysium::Core::Template::Functional::Move(Right);
	}

	template<Concepts::Character C, class Traits>
	inline StringView<C, Traits>::~StringView()
	{ }

	template<Concepts::Character C, class Traits>
	inline StringView<C, Traits>& StringView<C, Traits>::operator=(const StringView& Source)
	{
		if (this != &Source)
		{
			_Length = Source._Length;
			_Data = Source._Data;
		}
		return *this;
	}

	template<Concepts::Character C, class Traits>
	inline StringView<C, Traits>& StringView<C, Traits>::operator=(StringView&& Right) noexcept
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

	template<Concepts::Character C, class Traits>
	inline StringView<C, Traits>::CharacterReference StringView<C, Traits>::operator[](const Elysium::Core::Template::System::size Index)
	{
		if (Index >= _Length)
		{
			//throw IndexOutOfRangeException();
		}

		return (CharacterReference)_Data[Index];
	}

	template<Concepts::Character C, class Traits>
	inline StringView<C, Traits>::ConstCharacterReference StringView<C, Traits>::operator[](const Elysium::Core::Template::System::size Index) const
	{
		if (Index >= _Length)
		{
			//throw IndexOutOfRangeException();
		}

		return _Data[Index];
	}

	template<Concepts::Character C, class Traits>
	inline const bool StringView<C, Traits>::operator==(const StringView& Other) const noexcept
	{
		if (this == &Other)
		{
			return true;
		}
		return _Data == Other._Data && _Length == Other._Length;
	}

	template<Concepts::Character C, class Traits>
	inline const bool StringView<C, Traits>::operator!=(const StringView& Other) const noexcept
	{
		if (this == &Other)
		{
			return false;
		}
		return _Data != Other._Data || _Length != Other._Length;
	}

	template<Concepts::Character C, class Traits>
	inline const bool StringView<C, Traits>::operator<(const StringView& Other) const noexcept
	{
		if (this == &Other)
		{
			return false;
		}
		return _Data == Other._Data && _Length < Other._Length;
	}

	template<Concepts::Character C, class Traits>
	inline const bool StringView<C, Traits>::operator>(const StringView& Other) const noexcept
	{
		if (this == &Other)
		{
			return false;
		}
		return _Data == Other._Data && _Length > Other._Length;
	}

	template<Concepts::Character C, class Traits>
	inline const bool StringView<C, Traits>::operator<=(const StringView& Other) const noexcept
	{
		if (this == &Other)
		{
			return true;
		}
		return _Data == Other._Data && _Length <= Other._Length;
	}

	template<Concepts::Character C, class Traits>
	inline const bool StringView<C, Traits>::operator>=(const StringView& Other) const noexcept
	{
		if (this == &Other)
		{
			return true;
		}
		return _Data == Other._Data && _Length >= Other._Length;
	}

	template<Concepts::Character C, class Traits>
	inline const bool StringView<C, Traits>::IsNullOrEmtpy(const StringView& Value)
	{
		return Traits::IsNullOrEmpty(Value._Data);
	}

	template<Concepts::Character C, class Traits>
	inline const Elysium::Core::Template::System::size StringView<C, Traits>::GetLength() const
	{
		return _Length;
	}

	template<Concepts::Character C, class Traits>
	inline const Elysium::Core::Template::System::size StringView<C, Traits>::IndexOf(ConstCharacter Value) const noexcept
	{
		return Traits::IndexOf(_Data, _Length, Value);
	}

	template<Concepts::Character C, class Traits>
	inline const Elysium::Core::Template::System::size StringView<C, Traits>::IndexOf(ConstCharacter Value, const Elysium::Core::Template::System::size StartIndex) const noexcept
	{
		return Traits::IndexOf(&_Data[StartIndex], _Length - StartIndex, Value);
	}

	template<Concepts::Character C, class Traits>
	inline const Elysium::Core::Template::System::size StringView<C, Traits>::IndexOf(ConstCharacterPointer Sequence) const noexcept
	{
		return Traits::IndexOf(_Data, _Length, Sequence);
	}

	template<Concepts::Character C, class Traits>
	inline const Elysium::Core::Template::System::size StringView<C, Traits>::IndexOf(ConstCharacterPointer Sequence, const Elysium::Core::Template::System::size StartIndex) const noexcept
	{
		return Traits::IndexOf(&_Data[StartIndex], _Length - StartIndex, Sequence);
	}

	template<Concepts::Character C, class Traits>
	inline const System::size StringView<C, Traits>::IndexOfAny(ConstCharacterPointer Sequence, const System::size SequenceLength) const noexcept
	{
		return Traits::IndexOfAny(_Data, _Length, Sequence, SequenceLength);
	}

	template<Concepts::Character C, class Traits>
	inline const System::size StringView<C, Traits>::IndexOfAny(ConstCharacterPointer Sequence, const System::size SequenceLength, const System::size StartIndex) const noexcept
	{
		return Traits::IndexOfAny(&_Data[StartIndex], _Length - StartIndex, Sequence, SequenceLength);
	}

	template<Concepts::Character C, class Traits>
	inline const Elysium::Core::Template::System::size StringView<C, Traits>::LastIndexOf(ConstCharacter Value) const noexcept
	{
		return Traits::LastIndexOf(_Data, _Length, Value);
	}

	template<Concepts::Character C, class Traits>
	inline const Elysium::Core::Template::System::size StringView<C, Traits>::LastIndexOf(ConstCharacterPointer Sequence) const noexcept
	{
		return Traits::LastIndexOf(_Data, _Length, Sequence);
	}

	template<Concepts::Character C, class Traits>
	inline Container::Vector<StringView<C, Traits>> StringView<C, Traits>::Split(ConstCharacter Delimiter) const
	{
		Container::Vector<StringView<C, Traits>> Result = Container::Vector<StringView<C, Traits>>();
		System::size StartIndex = 0;
		System::size Length = 0;

		for (System::size i = 0; i < _Length; i++)
		{
			Length = Traits::IndexOf(&_Data[StartIndex], _Length - StartIndex, Delimiter);
			if (Length == static_cast<System::size>(-1))
			{
				if (_Length - StartIndex > 0)
				{
					Result.PushBack(Functional::Move(StringView<C, Traits>(&_Data[StartIndex], Length - StartIndex)));
				}
				break;
			}
			Result.PushBack(Functional::Move(StringView<C, Traits>(&_Data[StartIndex], Length)));
			StartIndex += Length + 1;
		}

		return Result;
	}

	template<Concepts::Character C, class Traits>
	inline Container::Vector<StringView<C, Traits>> StringView<C, Traits>::Split(ConstCharacterPointer DelimiterSequence) const
	{
		Container::Vector<StringView<C, Traits>> Result = Container::Vector<StringView<C, Traits>>();

		System::size DelimiterLength = Elysium::Core::Template::Text::CharacterTraits<C>::GetLength(DelimiterSequence);
		System::size StartIndex = 0;
		System::size Length = 0;

		for (System::size i = 0; i < _Length; i++)
		{
			Length = Traits::IndexOf(&_Data[StartIndex], _Length - StartIndex, DelimiterSequence);
			if (Length == static_cast<System::size>(-1))
			{
				if (_Length - StartIndex > 0)
				{
					Result.PushBack(Functional::Move(StringView<C, Traits>(&_Data[StartIndex], Length - StartIndex)));
				}
				break;
			}
			Result.PushBack(Functional::Move(StringView<C, Traits>(&_Data[StartIndex], Length)));
			StartIndex += Length + DelimiterLength;
		}

		return Result;


		/*
		while (true)
		{
			Length = IndexOf(DelimiterSequence, StartIndex);
			if (Length == static_cast<Elysium::Core::Template::System::size>(-1))
			{
				if (_Length - StartIndex > 0)
				{
					Result.PushBack(Functional::Move(StringView<C, Traits>(&_Data[StartIndex], _Length - StartIndex)));
				}
				break;
			}
			Result.PushBack(Elysium::Core::Template::Functional::Move(StringView<C, Traits>(&_Data[StartIndex], Length - StartIndex)));
			StartIndex += (Length - StartIndex) + DelimiterLength;
		}
	
		return Result;
		*/
	}

	template<Concepts::Character C, class Traits>
	inline StringView<C, Traits> StringView<C, Traits>::Substringview(const Elysium::Core::Template::System::size StartIndex, const Elysium::Core::Template::System::size Length) const
	{
		return StringView<C>(&_Data[StartIndex], Length);
	}

	template<Concepts::Character C, class Traits>
	inline StringView<C, Traits>::CorrespondingString StringView<C, Traits>::ToString() const
	{
		return CorrespondingString(_Data, _Length);
	}
}
#endif
