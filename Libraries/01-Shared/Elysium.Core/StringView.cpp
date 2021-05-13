#include "StringView.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

#ifndef _XSTRING_
#include <xstring>	// std::char_traits
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LIST
#include "List.hpp"
#endif

#ifndef ELYSIUM_CORE_INDEXOUTOFRANGEEXCEPTION
#include "IndexOutOfRangeException.hpp"
#endif

Elysium::Core::StringView::StringView()
	: _Length(0), _Data(nullptr)
{ }

Elysium::Core::StringView::StringView(char8_t* Input)
	: _Length(std::char_traits<char8_t>::length(Input)), _Data(Input)
{ }

Elysium::Core::StringView::StringView(char8_t* Input, size_t Length)
	: _Length(Length), _Data(Input)
{ }

Elysium::Core::StringView::StringView(const String& Input)
	: _Length(Input.GetLength()), _Data((char8_t*)&Input[0])
{ }

Elysium::Core::StringView::StringView(const String& Input, size_t Length)
	: _Length(Length), _Data((char8_t*)&Input[0])
{ }

Elysium::Core::StringView::StringView(const String& Input, size_t Offset, size_t Length)
	: _Length(Length), _Data((char8_t*)&Input[Offset])
{ }

Elysium::Core::StringView::StringView(const StringView& Source)
	: _Length(Source._Length), _Data(Source._Data)
{ }

Elysium::Core::StringView::StringView(StringView&& Right) noexcept
	: _Length(0), _Data(nullptr)
{
	*this = std::move(Right);
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
		_Length = Right._Length;
		_Data = Right._Data;

		Right._Length = 0;
		Right._Data = nullptr;
	}
	return *this;
}

char8_t& Elysium::Core::StringView::operator[](size_t Index)
{
	if (Index >= _Length)
	{
		throw IndexOutOfRangeException();
	}
	return _Data[Index];
}

const char8_t& Elysium::Core::StringView::operator[](size_t Index) const
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

	for (size_t i = 0; i < _Length; i++)
	{
		if (_Data[i] != Other[i])
		{
			return false;
		}
	}

	return true;
}

const size_t Elysium::Core::StringView::GetLength() const
{
	return _Length;
}

const size_t Elysium::Core::StringView::IndexOf(const char8_t Value) const
{
	const char8_t* CharPointer = std::char_traits<char8_t>::find(_Data, _Length, Value);
	return CharPointer == nullptr ? static_cast<size_t>(-1) : CharPointer - _Data;
}

const size_t Elysium::Core::StringView::IndexOf(const char8_t Value, const size_t StartIndex) const
{
	const char8_t* CharPointer = std::char_traits<char8_t>::find(&_Data[StartIndex], _Length - StartIndex, Value);
	return CharPointer == nullptr ? static_cast<size_t>(-1) : CharPointer - &_Data[StartIndex];
}

const size_t Elysium::Core::StringView::IndexOf(const char8_t* Value) const
{
	size_t Index = 0;
	size_t SizeOfValue = std::char_traits<char8_t>::length(Value);
	while (true)
	{
		size_t CurrentIndex = IndexOf(Value[0], Index);
		if (CurrentIndex == static_cast<size_t>(-1))
		{
			return CurrentIndex;
		}

		Index += CurrentIndex;
		if (Index + SizeOfValue > _Length)
		{
			return static_cast<size_t>(-1);
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

const size_t Elysium::Core::StringView::IndexOf(const char8_t* Value, const size_t StartIndex) const
{
	size_t Index = StartIndex;
	size_t SizeOfValue = std::char_traits<char8_t>::length(Value);
	while (true)
	{
		size_t CurrentIndex = IndexOf(Value[0], Index);
		if (CurrentIndex == static_cast<size_t>(-1))
		{
			return CurrentIndex;
		}

		Index += CurrentIndex;
		if (Index + SizeOfValue > _Length)
		{
			return static_cast<size_t>(-1);
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

const size_t Elysium::Core::StringView::IndexOf(const String& Value, const size_t StartIndex) const
{
	return IndexOf(Value[StartIndex]);
}

const size_t Elysium::Core::StringView::LastIndexOf(const char8_t* Value) const
{	// ToDo
	throw 1;
}

void Elysium::Core::StringView::Split(const char8_t Delimiter, Collections::Template::List<StringView>& Views) const
{
	size_t StartIndex = 0;
	size_t Length = 0;

	while (true)
	{
		Length = IndexOf(Delimiter, StartIndex);
		if (Length == static_cast<size_t>(-1))
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
	size_t DelimiterLength = std::char_traits<char8_t>::length(Delimiter);
	size_t StartIndex = 0;
	size_t Length = 0;

	while (true)
	{
		Length = IndexOf(Delimiter, StartIndex);
		if (Length == static_cast<size_t>(-1))
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

Elysium::Core::StringView Elysium::Core::StringView::Substringview(const size_t StartIndex) const
{
	return StringView(&_Data[StartIndex], _Length - StartIndex);
}

Elysium::Core::StringView Elysium::Core::StringView::Substringview(const size_t StartIndex, const size_t Length) const
{
	return StringView(&_Data[StartIndex], Length);
}
