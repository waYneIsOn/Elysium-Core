#include "StringView.hpp"

#ifndef _XSTRING_
#include <xstring>
#endif

#ifndef ELYSIUM_CORE_INDEXOUTOFRANGEEXCEPTION
#include "IndexOutOfRangeException.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "NotImplementedException.hpp"
#endif

Elysium::Core::StringView::StringView()
	: _Data(nullptr), _Length(0)
{
}
Elysium::Core::StringView::StringView(char16_t * Input)
	: _Data(&Input[0]), _Length(std::char_traits<char16_t>::length(Input))
{
}
Elysium::Core::StringView::StringView(char16_t * Input, size_t Length)
	: _Data(&Input[0]), _Length(Length)
{
}
Elysium::Core::StringView::StringView(const Elysium::Core::String & Input)
	: _Data(&Input[0]), _Length(Input.GetLength())
{
}
Elysium::Core::StringView::StringView(const Elysium::Core::String & Input, size_t Length)
	: _Data(&Input[0]), _Length(Length)
{
}
Elysium::Core::StringView::StringView(const Elysium::Core::String & Input, size_t Offset, size_t Length)
	: _Data(&Input[Offset]), _Length(Length)
{
}
Elysium::Core::StringView::StringView(const StringView & Source)
	: _Data(Source._Data), _Length(Source._Length)
{
}
Elysium::Core::StringView::StringView(StringView && Right) noexcept
{
	*this = std::move(Right);
}
Elysium::Core::StringView::~StringView()
{
}

Elysium::Core::StringView & Elysium::Core::StringView::operator=(const StringView & Value)
{
	_Length = Value._Length;
	_Data = Value._Data;
	return *this;
}
Elysium::Core::StringView & Elysium::Core::StringView::operator=(StringView && Right) noexcept
{
	if (this != &Right)
	{
		// grab Right's objects
		_Data = Right._Data;
		_Length = Right._Length;

		// release Right's objects
		Right._Data = nullptr;
		Right._Length = 0;
	}

	return *this;
}

bool Elysium::Core::StringView::operator==(const StringView & Other) const
{
	if (this == &Other)
	{
		return true;
	}

	return _Data == Other._Data && _Length == Other._Length;
}
bool Elysium::Core::StringView::operator!=(const StringView & Other) const
{
	if (this == &Other)
	{
		return false;
	}

	return _Data != Other._Data || _Length != Other._Length;
}
bool Elysium::Core::StringView::operator<(const StringView & Other) const
{
	return _Data == Other._Data && _Length < Other._Length;
}
bool Elysium::Core::StringView::operator>(const StringView & Other) const
{
	return _Data == Other._Data && _Length > Other._Length;
}
bool Elysium::Core::StringView::operator<=(const StringView & Other) const
{
	if (this == &Other)
	{
		return true;
	}

	return _Data == Other._Data && _Length <= Other._Length;
}
bool Elysium::Core::StringView::operator>=(const StringView & Other) const
{
	if (this == &Other)
	{
		return true;
	}

	return _Data == Other._Data && _Length >= Other._Length;
}

const size_t Elysium::Core::StringView::GetLength() const
{
	return _Length;
}

size_t Elysium::Core::StringView::IndexOf(const char16_t Value) const
{
	const char16_t* CharPointer = std::char_traits<char16_t>::find(_Data, _Length, Value);
	return CharPointer == nullptr ? static_cast<const char16_t>(-1) : CharPointer - _Data;
}
size_t Elysium::Core::StringView::IndexOf(const char16_t Value, const size_t StartIndex) const
{
	const char16_t* CharPointer = std::char_traits<char16_t>::find(&_Data[StartIndex], _Length - StartIndex, Value);
	return CharPointer == nullptr ? static_cast<size_t>(-1) : CharPointer - &_Data[StartIndex];
}
size_t Elysium::Core::StringView::IndexOf(const char16_t * Value) const
{
	size_t Index = 0;
	size_t SizeOfValue = std::char_traits<char16_t>::length(Value);
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
size_t Elysium::Core::StringView::IndexOf(const char16_t * Value, const size_t StartIndex) const
{
	size_t Index = StartIndex;
	size_t SizeOfValue = std::char_traits<char16_t>::length(Value);
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
size_t Elysium::Core::StringView::IndexOf(const String & Value, const size_t StartIndex) const
{
	return IndexOf(Value[StartIndex]);
}
void Elysium::Core::StringView::Split(const char16_t Delimiter, Elysium::Core::Collections::Generic::List<StringView> & Views) const
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
void Elysium::Core::StringView::Split(const char16_t* Delimiter, Elysium::Core::Collections::Generic::List<StringView> & Views) const
{
	size_t DelimiterLength = std::char_traits<char16_t>::length(Delimiter);
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

char16_t & Elysium::Core::StringView::operator[](size_t Index) const
{
	if (Index > _Length)	// not >= because or \0
	{
		throw IndexOutOfRangeException();
	}

	return _Data[Index];
}

Elysium::Core::StringView::operator Elysium::Core::String() const
{
	return String(_Data, _Length);
}
