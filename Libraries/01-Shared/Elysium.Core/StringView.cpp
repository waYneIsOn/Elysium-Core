#include "StringView.hpp"

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LIST
#include "List.hpp"
#endif

#ifndef ELYSIUM_CORE_INDEXOUTOFRANGEEXCEPTION
#include "IndexOutOfRangeException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRINGTRAITS
#include "../Elysium.Core.Template/StringTraits.hpp"
#endif

Elysium::Core::StringView::StringView()
	: _Length(0), _Data(nullptr)
{ }

Elysium::Core::StringView::StringView(char8_t* Input)
	: _Length(Elysium::Core::Template::Text::StringTraits<char8_t>::GetLength(Input)), _Data(Input)
{ }

Elysium::Core::StringView::StringView(char8_t* Input, Elysium::Core::size Length)
	: _Length(Length), _Data(Input)
{ }

Elysium::Core::StringView::StringView(const String& Input)
	: _Length(Input.GetLength()), _Data((char8_t*)&Input[0])
{ }

Elysium::Core::StringView::StringView(const String& Input, Elysium::Core::size Length)
	: _Length(Length), _Data((char8_t*)&Input[0])
{ }

Elysium::Core::StringView::StringView(const String& Input, Elysium::Core::size Offset, Elysium::Core::size Length)
	: _Length(Length), _Data((char8_t*)&Input[Offset])
{ }

Elysium::Core::StringView::StringView(const StringView& Source)
	: _Length(Source._Length), _Data(Source._Data)
{ }

Elysium::Core::StringView::StringView(StringView&& Right) noexcept
	: _Length(0), _Data(nullptr)
{
	*this = Elysium::Core::Template::Functional::Move(Right);
}

Elysium::Core::StringView::~StringView()
{ }

Elysium::Core::StringView& Elysium::Core::StringView::operator=(const StringView & Source)
{
	if (this != &Source)
	{
		_Length = Source._Length;
		_Data = Source._Data;
	}
	return *this;
}

Elysium::Core::StringView& Elysium::Core::StringView::operator=(StringView&& Right) noexcept
{
	if (this != &Right)
	{
		_Length = Elysium::Core::Template::Functional::Move(Right._Length);
		_Data = Elysium::Core::Template::Functional::Move(Right._Data);

		Right._Length = 0;
		Right._Data = nullptr;
	}
	return *this;
}

char8_t& Elysium::Core::StringView::operator[](Elysium::Core::size Index)
{
	if (Index >= _Length)
	{
		throw IndexOutOfRangeException();
	}
	return _Data[Index];
}

const char8_t& Elysium::Core::StringView::operator[](Elysium::Core::size Index) const
{
	if (Index >= _Length)
	{
		throw IndexOutOfRangeException();
	}
	return _Data[Index];
}

Elysium::Core::StringView::operator Elysium::Core::String() const
{
	return Elysium::Core::String(_Data, _Length);
}

const bool Elysium::Core::StringView::operator==(const StringView& Other) const
{
	if (this == &Other)
	{
		return true;
	}
	return _Data == Other._Data && _Length == Other._Length;
}

const bool Elysium::Core::StringView::operator!=(const StringView& Other) const
{
	if (this == &Other)
	{
		return false;
	}
	return _Data != Other._Data || _Length != Other._Length;
}

const bool Elysium::Core::StringView::operator<(const StringView& Other) const
{
	return _Data == Other._Data && _Length < Other._Length;
}

const bool Elysium::Core::StringView::operator>(const StringView& Other) const
{
	return _Data == Other._Data && _Length > Other._Length;
}

const bool Elysium::Core::StringView::operator<=(const StringView& Other) const
{
	if (this == &Other)
	{
		return true;
	}
	return _Data == Other._Data && _Length <= Other._Length;
}

const bool Elysium::Core::StringView::operator>=(const StringView& Other) const
{
	if (this == &Other)
	{
		return true;
	}
	return _Data == Other._Data && _Length >= Other._Length;
}

const bool Elysium::Core::StringView::operator==(const String& Other) const
{
	/*
	if (this == &Other)
	{
		return true;
	}
	*/
	if (_Length > Other.GetLength())
	{
		return false;
	}

	for (Elysium::Core::size i = 0; i < _Length; i++)
	{
		if (_Data[i] != Other[i])
		{
			return false;
		}
	}

	return true;
}

const Elysium::Core::size Elysium::Core::StringView::GetLength() const
{
	return _Length;
}

const Elysium::Core::size Elysium::Core::StringView::IndexOf(const char8_t Value) const
{
	const char8_t* CharPointer = Elysium::Core::Template::Text::StringTraits<char8_t>::Find(_Data, _Length, Value);
	return CharPointer == nullptr ? static_cast<Elysium::Core::size>(-1) : CharPointer - _Data;
}

const Elysium::Core::size Elysium::Core::StringView::IndexOf(const char8_t Value, const Elysium::Core::size StartIndex) const
{
	const char8_t* CharPointer = Elysium::Core::Template::Text::StringTraits<char8_t>::Find(&_Data[StartIndex], _Length - StartIndex, Value);
	return CharPointer == nullptr ? static_cast<Elysium::Core::size>(-1) : CharPointer - &_Data[StartIndex];
}

const Elysium::Core::size Elysium::Core::StringView::IndexOf(const char8_t* Value) const
{
	Elysium::Core::size Index = 0;
	Elysium::Core::size SizeOfValue = Elysium::Core::Template::Text::StringTraits<char8_t>::GetLength(Value);
	while (true)
	{
		Elysium::Core::size CurrentIndex = IndexOf(Value[0], Index);
		if (CurrentIndex == static_cast<Elysium::Core::size>(-1))
		{
			return CurrentIndex;
		}

		Index += CurrentIndex;
		if (Index + SizeOfValue > _Length)
		{
			return static_cast<Elysium::Core::size>(-1);
		}

		bool Found = true;
		for (int i = 1; i < SizeOfValue; i++)
		{
			if (_Data[Index + i] != Value[i])
			{
				Found = false;
				break;
			}
		}

		if (Found)
		{
			return Index;
		}
		Index++;
	}
}

const Elysium::Core::size Elysium::Core::StringView::IndexOf(const char8_t* Value, const Elysium::Core::size StartIndex) const
{
	Elysium::Core::size Index = StartIndex;
	Elysium::Core::size SizeOfValue = Elysium::Core::Template::Text::StringTraits<char8_t>::GetLength(Value);
	while (true)
	{
		Elysium::Core::size CurrentIndex = IndexOf(Value[0], Index);
		if (CurrentIndex == static_cast<Elysium::Core::size>(-1))
		{
			return CurrentIndex;
		}

		Index += CurrentIndex;
		if (Index + SizeOfValue > _Length)
		{
			return static_cast<Elysium::Core::size>(-1);
		}

		bool Found = true;
		for (int i = 1; i < SizeOfValue; i++)
		{
			if (_Data[Index + i] != Value[i])
			{
				Found = false;
				break;
			}
		}

		if (Found)
		{
			return Index;
		}
		Index++;
	}
}

const Elysium::Core::size Elysium::Core::StringView::IndexOf(const String& Value, const Elysium::Core::size StartIndex) const
{
	return IndexOf(Value[StartIndex]);
}

const Elysium::Core::size Elysium::Core::StringView::LastIndexOf(const char8_t* Value) const
{	// ToDo
	throw 1;
}

void Elysium::Core::StringView::Split(const char8_t Delimiter, Collections::Template::List<StringView>& Views) const
{
	Elysium::Core::size StartIndex = 0;
	Elysium::Core::size Length = 0;

	while (true)
	{
		Length = IndexOf(Delimiter, StartIndex);
		if (Length == static_cast<Elysium::Core::size>(-1))
		{
			if (_Length - StartIndex > 0)
			{
				Views.Add(StringView(&_Data[StartIndex], _Length - StartIndex));
			}
			break;
		}
		Views.Add(StringView(&_Data[StartIndex], Length));
		StartIndex += Length + 1;
	}
}

void Elysium::Core::StringView::Split(const char8_t* Delimiter, Collections::Template::List<StringView>& Views) const
{
	Elysium::Core::size DelimiterLength = Elysium::Core::Template::Text::StringTraits<char8_t>::GetLength(Delimiter);
	Elysium::Core::size StartIndex = 0;
	Elysium::Core::size Length = 0;

	while (true)
	{
		Length = IndexOf(Delimiter, StartIndex);
		if (Length == static_cast<Elysium::Core::size>(-1))
		{
			if (_Length - StartIndex > 0)
			{
				Views.Add(StringView(&_Data[StartIndex], _Length - StartIndex));
			}
			break;
		}
		Views.Add(StringView(&_Data[StartIndex], Length - StartIndex));
		StartIndex += (Length - StartIndex) + DelimiterLength;
	}
}

Elysium::Core::StringView Elysium::Core::StringView::Substringview(const Elysium::Core::size StartIndex) const
{
	return StringView(&_Data[StartIndex], _Length - StartIndex);
}

Elysium::Core::StringView Elysium::Core::StringView::Substringview(const Elysium::Core::size StartIndex, const Elysium::Core::size Length) const
{
	return StringView(&_Data[StartIndex], Length);
}

const bool Elysium::Core::StringView::IsNullOrEmtpy(const StringView& Value)
{
	return Value._Data == nullptr || (Value._Data != nullptr && Value._Length == 1);
}
