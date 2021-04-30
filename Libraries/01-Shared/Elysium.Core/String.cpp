#include "String.hpp"

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

const Elysium::Core::String Elysium::Core::String::Empty = Elysium::Core::String();

Elysium::Core::String::String()
	: _Length(0), _Data(nullptr)
{
	//*this = Elysium::Core::String::Empty;
}

Elysium::Core::String::String(const size_t Length)
	: _Length(Length), _Data(new char8_t[_Length + 1])
{
	std::memset(_Data, 0, _Length + 1);
}

Elysium::Core::String::String(const char8_t* Value)
	: _Length(Value == nullptr ? 0 : std::char_traits<char8_t>::length(Value)), _Data(_Length == 0 ? nullptr : new char8_t[_Length + 1])
{
	if (_Data != nullptr)
	{
		memcpy(_Data, Value, (_Length + 1) * sizeof(char8_t));
	}
}

Elysium::Core::String::String(const char8_t* Value, const size_t Length)
	: _Length(Value == nullptr ? 0 : Length), _Data(_Length == 0 ? nullptr : new char8_t[_Length + 1])
{
	if (_Data != nullptr)
	{
		memcpy(_Data, Value, _Length * sizeof(char8_t));
		_Data[_Length] = _NullTerminationChar;
	}
}

Elysium::Core::String::String(const String& Source)
	: _Length(Source._Length), _Data(_Length == 0 ? nullptr : new char8_t[_Length + 1])
{
	if (_Data != nullptr)
	{
		memcpy(_Data, Source._Data, (_Length + 1) * sizeof(char8_t));
	}
}

Elysium::Core::String::String(String&& Right) noexcept
	: _Length(0), _Data(nullptr)
{
	*this = std::move(Right);
}

Elysium::Core::String::~String()
{
	if (_Data != nullptr)
	{
		delete[] _Data;
		_Data = nullptr;
	}
}

Elysium::Core::String& Elysium::Core::String::operator=(const char8_t* Value)
{
	if (_Data != nullptr)
	{
		delete[] _Data;
	}

	_Length = Value == nullptr ? 0 : std::char_traits<char8_t>::length(Value);
	_Data = _Length == 0 ? nullptr : new char8_t[_Length + 1];
	if (_Data != nullptr)
	{
		memcpy(_Data, Value, (_Length + 1) * sizeof(char8_t));
	}
	return *this;
}

Elysium::Core::String& Elysium::Core::String::operator=(const String& Source)
{
	if (this != &Source)
	{
		if (_Data != nullptr)
		{
			delete[] _Data;
		}

		_Length = Source._Length;
		_Data = _Length == 0 ? nullptr : new char8_t[_Length + 1];
		if (_Data != nullptr)
		{
			memcpy(_Data, Source._Data, (_Length + 1) * sizeof(char8_t));
		}
	}
	return *this;
}

Elysium::Core::String& Elysium::Core::String::operator=(String&& Right) noexcept
{
	if (this != &Right)
	{
		if (_Data != nullptr)
		{
			delete[] _Data;
		}

		_Length = Right._Length;
		_Data = Right._Data;

		Right._Length = 0;
		Right._Data = nullptr;
	}
	return *this;
}

bool Elysium::Core::String::operator==(const String& Other) const
{
	if (this == &Other)
	{
		return true;
	}
	if (_Length != Other._Length)
	{
		return false;
	}
	return std::char_traits<char8_t>::compare(_Data, Other._Data, Other._Length) == 0;
}

bool Elysium::Core::String::operator!=(const String& Other) const
{
	if (this == &Other)
	{
		return false;
	}
	return std::char_traits<char8_t>::compare(_Data, Other._Data, Other._Length) != 0;
}

bool Elysium::Core::String::operator<(const String& Other) const
{
	if (this == &Other)
	{
		return false;
	}
	return std::char_traits<char8_t>::compare(_Data, Other._Data, Other._Length) < 0;
}

bool Elysium::Core::String::operator>(const String& Other) const
{
	if (this == &Other)
	{
		return false;
	}
	return std::char_traits<char8_t>::compare(_Data, Other._Data, Other._Length) > 0;
}

bool Elysium::Core::String::operator<=(const String Other) const
{
	if (this == &Other)
	{
		return true;
	}
	return std::char_traits<char8_t>::compare(_Data, Other._Data, Other._Length) <= 0;
}

bool Elysium::Core::String::operator>=(const String& Other) const
{
	if (this == &Other)
	{
		return true;
	}
	return std::char_traits<char8_t>::compare(_Data, Other._Data, Other._Length) >= 0;
}

char8_t& Elysium::Core::String::operator[](const size_t Index) const
{
	if (Index >= _Length)
	{
		throw IndexOutOfRangeException();
	}
	return _Data[Index];
}

const size_t Elysium::Core::String::GetLength() const throw()
{
	return _Length;
}

const size_t Elysium::Core::String::IndexOf(const char8_t Value) const
{
	const char8_t* CharPointer = std::char_traits<char8_t>::find(_Data, _Length, Value);
	return CharPointer == nullptr ? static_cast<size_t>(-1) : CharPointer - _Data;
}

const size_t Elysium::Core::String::IndexOf(const char8_t Value, const size_t StartIndex) const
{
	const char8_t* CharPointer = std::char_traits<char8_t>::find(&_Data[StartIndex], _Length - StartIndex, Value);
	return CharPointer == nullptr ? static_cast<size_t>(-1) : CharPointer - &_Data[StartIndex];
}

const size_t Elysium::Core::String::IndexOf(const char8_t* Value) const
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

const size_t Elysium::Core::String::IndexOf(const char8_t* Value, const size_t StartIndex) const
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

const size_t Elysium::Core::String::IndexOf(const String& Value, const size_t StartIndex) const
{
	return IndexOf(Value._Data[StartIndex]);
}

const size_t Elysium::Core::String::LastIndexOf(const char8_t Value) const
{
	char8_t* CharPointer = nullptr;
	for (size_t i = _Length; i > 0; i--)
	{
		if (_Data[i - 1] == Value)
		{
			CharPointer = &_Data[i - 1];
			break;
		}
	}
	return CharPointer == nullptr ? static_cast<size_t>(-1) : CharPointer - _Data;
}

const size_t Elysium::Core::String::LastIndexOf(const char8_t* Value) const
{
	// ToDo
	return size_t(-1);
}

const size_t Elysium::Core::String::LastIndexOf(const char8_t* Value, const size_t StartIndex) const
{	// ToDo
	return size_t(-1);
}

const size_t Elysium::Core::String::LastIndexOf(const String& Value, const size_t StartIndex) const
{	// ToDo
	return size_t(-1);
}

void Elysium::Core::String::Split(const char8_t Delimiter, Collections::Template::List<String>& Target) const
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

void Elysium::Core::String::Split(const char8_t* Delimiter, Collections::Template::List<String>& Target) const
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
				Target.Add(String(&_Data[StartIndex], _Length - StartIndex));
			}
			break;
		}
		Target.Add(String(&_Data[StartIndex], Length - StartIndex));
		StartIndex += (Length - StartIndex) + DelimiterLength;
	}
}

const bool Elysium::Core::String::StartsWith(const char8_t* Value) const
{
	size_t ValueLength = std::char_traits<char8_t>::length(Value);
	for (size_t i = 0; i < ValueLength; i++)
	{
		if (_Data[i] != Value[i])
		{
			return false;
		}
	}
	return true;
}

const bool Elysium::Core::String::EndsWith(const char8_t* Value) const
{
	size_t ValueLength = std::char_traits<char8_t>::length(Value);
	for (size_t i = _Length - ValueLength; i < _Length; i++)
	{
		if (_Data[i] != Value[i])
		{
			return false;
		}
	}
	return true;
}

Elysium::Core::String Elysium::Core::String::Substring(const size_t StartIndex) const
{
	return String(&_Data[StartIndex], _Length - StartIndex);
}

Elysium::Core::String Elysium::Core::String::Substring(const size_t StartIndex, const size_t Length) const
{
	return String(&_Data[StartIndex], Length);
}

const bool Elysium::Core::String::IsNull(const String& Value)
{
	return Value._Data == nullptr;
}

const bool Elysium::Core::String::IsEmpty(const String& Value)
{
	return Value._Data != nullptr && Value._Length == 1;
}

const bool Elysium::Core::String::IsNullOrEmtpy(const String& Value)
{
	return Value._Data == nullptr || (Value._Data != nullptr && Value._Length == 1);
}
