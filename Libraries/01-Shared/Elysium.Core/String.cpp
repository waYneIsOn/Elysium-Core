#include "String.hpp"

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LIST
#include "List.hpp"
#endif

#ifndef _XSTRING_
#include <xstring>
#endif

#ifndef ELYSIUM_CORE_INDEXOUTOFRANGEEXCEPTION
#include "IndexOutOfRangeException.hpp"
#endif

#ifndef ELYSIUM_CORE_ARGUMENTNULLEXCEPTION
#include "ArgumentNullException.hpp"
#endif

Elysium::Core::String::String()
	: _Length((size_t)0), _Data(nullptr)
{
}
Elysium::Core::String::String(size_t Length)
	: _Length(Length), _Data(new char16_t[_Length + sizeof(char16_t)])
{
}
Elysium::Core::String::String(const char16_t* Value)
	: Elysium::Core::String(Value == nullptr ? 0 : std::char_traits<char16_t>::length(Value))
{
	memcpy(_Data, Value, _Length * sizeof(char16_t));
	_Data[_Length] = u'\0';
}
Elysium::Core::String::String(const char16_t * Value, size_t Length)
	: Elysium::Core::String(Value == nullptr ? 0 : Length)
{
	memcpy(_Data, Value, _Length * sizeof(char16_t));
	_Data[_Length] = u'\0';
}
Elysium::Core::String::String(const String & Source)
	: Elysium::Core::String(Source._Length)
{
	memcpy(_Data, Source._Data, _Length * sizeof(char16_t));
	_Data[_Length] = u'\0';
}
Elysium::Core::String::String(String && Right) noexcept
	: _Length((size_t)0), _Data(nullptr)
{
	*this = std::move(Right);
}
Elysium::Core::String::~String()
{
	if (_Data != nullptr)
	{
		delete[] _Data;
	}
}

Elysium::Core::String & Elysium::Core::String::operator=(const String & Source)
{
	if (this != &Source)
	{
		if (_Data != nullptr)
		{
			delete[] _Data;
		}
		_Length = Source._Length;
		_Data = new char16_t[_Length + sizeof(char16_t)];
		memcpy(_Data, Source._Data, _Length * sizeof(char16_t));
		_Data[_Length] = u'\0';
	}
	return *this;
}
Elysium::Core::String & Elysium::Core::String::operator=(String && Right) noexcept
{
	if (this != &Right)
	{
		// release currently held objects
		if (_Data != nullptr)
		{
			delete[] _Data;
		}

		// grab Right's objects
		_Data = Right._Data;
		_Length = Right._Length;

		// release Right's objects
		Right._Data = nullptr;
		Right._Length = 0;
	}
	return *this;
}

Elysium::Core::String & Elysium::Core::String::operator=(const char16_t * Value)
{
	if (_Data != nullptr)
	{
		delete[] _Data;
	}
	_Length = std::char_traits<char16_t>::length(Value);
	_Data = new char16_t[_Length + sizeof(char16_t)];
	memcpy(_Data, Value, _Length * sizeof(char16_t));

	return *this;
}

char16_t & Elysium::Core::String::operator[](size_t Index) const
{
	if (Index > _Length)	// not >= because or \0
	{
		throw IndexOutOfRangeException();
	}

	return _Data[Index];
}

bool Elysium::Core::String::operator==(const String & Other) const
{
	if (this == &Other)
	{
		return true;
	}
	if (_Length != Other._Length)
	{
		return false;
	}
	return std::char_traits<char16_t>::compare(_Data, Other._Data, Other._Length) == 0;
}
bool Elysium::Core::String::operator!=(const String & Other) const
{
	if (this == &Other)
	{
		return false;
	}
	return std::char_traits<char16_t>::compare(_Data, Other._Data, Other._Length) != 0;
}
bool Elysium::Core::String::operator<(const String & Other) const
{
	if (this == &Other)
	{
		return false;
	}
	return std::char_traits<char16_t>::compare(_Data, Other._Data, Other._Length) < 0;
}
bool Elysium::Core::String::operator>(const String & Other) const
{
	if (this == &Other)
	{
		return false;
	}
	return std::char_traits<char16_t>::compare(_Data, Other._Data, Other._Length) > 0;
}
bool Elysium::Core::String::operator<=(const String & Other) const
{
	if (this == &Other)
	{
		return true;
	}
	return std::char_traits<char16_t>::compare(_Data, Other._Data, Other._Length) <= 0;
}
bool Elysium::Core::String::operator>=(const String & Other) const
{
	if (this == &Other)
	{
		return true;
	}
	return std::char_traits<char16_t>::compare(_Data, Other._Data, Other._Length) >= 0;
}

const size_t Elysium::Core::String::GetLength() const
{
	return _Length;
}
const char16_t * Elysium::Core::String::GetCharArray() const
{
	return _Data;
}

size_t Elysium::Core::String::IndexOf(const char16_t Value) const
{
	const char16_t* CharPointer = std::char_traits<char16_t>::find(_Data, _Length, Value);
	return CharPointer == nullptr ? static_cast<size_t>(-1) : CharPointer - _Data;
}
size_t Elysium::Core::String::IndexOf(const char16_t Value, const size_t StartIndex) const
{
	const char16_t* CharPointer = std::char_traits<char16_t>::find(&_Data[StartIndex], _Length - StartIndex, Value);
	return CharPointer == nullptr ? static_cast<size_t>(-1) : CharPointer - &_Data[StartIndex];
}
size_t Elysium::Core::String::IndexOf(const char16_t * Value) const
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
size_t Elysium::Core::String::IndexOf(const char16_t * Value, const size_t StartIndex) const
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
size_t Elysium::Core::String::IndexOf(const String & Value, const size_t StartIndex) const
{
	return IndexOf(Value._Data[StartIndex]);
}
void Elysium::Core::String::Split(const char16_t Delimiter, Elysium::Core::Collections::Template::List<Elysium::Core::String>& Target) const
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
				Target.Add(String(&_Data[StartIndex], _Length - StartIndex));
			}
			break;
		}
		Target.Add(String(&_Data[StartIndex], Length));
		StartIndex += Length + 1;
	}
}
void Elysium::Core::String::Split(const char16_t * Delimiter, Elysium::Core::Collections::Template::List<Elysium::Core::String>& Target) const
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
				Target.Add(String(&_Data[StartIndex], _Length - StartIndex));
			}
			break;
		}
		Target.Add(String(&_Data[StartIndex], Length - StartIndex));
		StartIndex += (Length - StartIndex) + DelimiterLength;
	}
}
bool Elysium::Core::String::StartsWith(const char16_t * Value) const
{
	size_t ValueLength = std::char_traits<char16_t>::length(Value);
	for (size_t i = 0; i < ValueLength; i++)
	{
		if (_Data[i] != Value[i])
		{
			return false;
		}
	}

	return true;
}

void Elysium::Core::String::Substring(size_t StartIndex, String * Result) const
{
	Elysium::Core::String::Substring(StartIndex, _Length - StartIndex, Result);
}
void Elysium::Core::String::Substring(size_t StartIndex, size_t Length, String * Result) const
{
	if (Result == nullptr)
	{
		throw ArgumentNullException(u"Result");
	}

	if (Result->_Data != nullptr)
	{
		delete[] Result->_Data;
	}
	Result->_Length = Length;
	Result->_Data = new char16_t[Result->_Length * sizeof(char16_t)];
	memcpy(Result->_Data, &_Data[StartIndex], Length * sizeof(char16_t));
	Result->_Data[Result->_Length] = u'\0';
}

bool Elysium::Core::String::IsNullOrEmtpy(const String & Value)
{
	return Value._Length == 0;
}
