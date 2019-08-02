#include "String.hpp"

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
	: _Length(Length), _Data(new ElysiumChar[_Length + sizeof(ElysiumChar)])
{
}
Elysium::Core::String::String(const ElysiumChar* Value)
	: Elysium::Core::String(Value == nullptr ? 0 : ElysiumStringLength(Value))
{
	memcpy(_Data, Value, _Length * sizeof(ElysiumChar));
#ifdef UNICODE
	_Data[_Length] = L'\0';
#else
	_Data[_Length] = '\0';
#endif 
}
Elysium::Core::String::String(const ElysiumChar * Value, size_t Length)
	: Elysium::Core::String(Value == nullptr ? 0 : Length)
{
	memcpy(_Data, Value, _Length * sizeof(ElysiumChar));
#ifdef UNICODE
	_Data[_Length] = L'\0';
#else
	_Data[_Length] = '\0';
#endif 
}
Elysium::Core::String::String(const String & Source)
	: Elysium::Core::String(Source._Length)
{
	memcpy(_Data, Source._Data, _Length * sizeof(ElysiumChar));
#ifdef UNICODE
	_Data[_Length] = L'\0';
#else
	_Data[_Length] = '\0';
#endif 
}
Elysium::Core::String::String(String && Right)
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
		_Data = new ElysiumChar[_Length + sizeof(ElysiumChar)];
		memcpy(_Data, Source._Data, _Length * sizeof(ElysiumChar));
#ifdef UNICODE
		_Data[_Length] = L'\0';
#else
		_Data[_Length] = '\0';
#endif 
	}
	return *this;
}
Elysium::Core::String & Elysium::Core::String::operator=(String && Right)
{
	if (this != &Right)
	{
		// release currently held objects
		if (_Data != nullptr)
		{
			delete _Data;
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

Elysium::Core::String & Elysium::Core::String::operator=(const ElysiumChar * Value)
{
	if (_Data != nullptr)
	{
		delete[] _Data;
	}
	_Length = ElysiumStringLength(Value);
	_Data = new ElysiumChar[_Length + sizeof(ElysiumChar)];
	memcpy(_Data, Value, _Length * sizeof(ElysiumChar));
#ifdef UNICODE
	_Data[_Length] = L'\0';
#else
	_Data[_Length] = '\0';
#endif 

	return *this;
}

ElysiumChar & Elysium::Core::String::operator[](size_t Index) const
{
	if (Index > _Length)	// not >= because or \0
	{
		throw IndexOutOfRangeException();
	}

	return _Data[Index];
}

bool Elysium::Core::String::operator==(const String & Other)
{
	if (this == &Other)
	{
		return true;
	}
	if (_Length != Other._Length)
	{
		return false;
	}

#ifdef UNICODE
	return wcscmp(_Data, Other._Data) == 0;
#else
	return strcmp(_Data, Other._Data) == 0;
#endif 
}
bool Elysium::Core::String::operator!=(const String & Other)
{
	if (this == &Other)
	{
		return false;
	}

#ifdef UNICODE
	return wcscmp(_Data, Other._Data) != 0;
#else
	return strcmp(_Data, Other._Data) != 0;
#endif 
}
bool Elysium::Core::String::operator<(const String & Other)
{
	if (this == &Other)
	{
		return false;
	}

#ifdef UNICODE
	return wcscmp(_Data, Other._Data) < 0;
#else
	return strcmp(_Data, Other._Data) < 0;
#endif 
}
bool Elysium::Core::String::operator>(const String & Other)
{
	if (this == &Other)
	{
		return false;
	}

#ifdef UNICODE
	return wcscmp(_Data, Other._Data) > 0;
#else
	return strcmp(_Data, Other._Data) > 0;
#endif 
}
bool Elysium::Core::String::operator<=(const String & Other)
{
	if (this == &Other)
	{
		return true;
	}

#ifdef UNICODE
	return wcscmp(_Data, Other._Data) <= 0;
#else
	return strcmp(_Data, Other._Data) <= 0;
#endif 
}
bool Elysium::Core::String::operator>=(const String & Other)
{
	if (this == &Other)
	{
		return true;
	}

#ifdef UNICODE
	return wcscmp(_Data, Other._Data) >= 0;
#else
	return strcmp(_Data, Other._Data) >= 0;
#endif 
}

bool Elysium::Core::operator==(const String & Left, const String & Right)
{
	if (&Left == &Right)
	{
		return true;
	}
	if (Left.GetLength() == Right.GetLength())
	{
		return false;
	}

#ifdef UNICODE
	// ToDo: use lstrcmpW instead?
	return wcscmp(&Left[0], &Right[0]) != 0;
#else
	return strcmp(&Left[0], &Right[0]) != 0;
#endif 
}
bool Elysium::Core::operator!=(const String & Left, const String & Right)
{
	if (&Left == &Right)
	{
		return false;
	}

#ifdef UNICODE
	return wcscmp(&Left[0], &Right[0]) != 0;
#else
	return strcmp(&Left[0], &Right[0]) != 0;
#endif 
}
bool Elysium::Core::operator<(const String & Left, const String & Right)
{
	if (&Left == &Right)
	{
		return false;
	}

#ifdef UNICODE
	return wcscmp(&Left[0], &Right[0]) < 0;
#else
	return strcmp(&Left[0], &Right[0]) < 0;
#endif 
}
bool Elysium::Core::operator>(const String & Left, const String & Right)
{
	if (&Left == &Right)
	{
		return false;
	}

#ifdef UNICODE
	return wcscmp(&Left[0], &Right[0]) > 0;
#else
	return strcmp(&Left[0], &Right[0]) > 0;
#endif 
}
bool Elysium::Core::operator<=(const String & Left, const String & Right)
{
	if (&Left == &Right)
	{
		return true;
	}

#ifdef UNICODE
	return wcscmp(&Left[0], &Right[0]) <= 0;
#else
	return strcmp(&Left[0], &Right[0]) <= 0;
#endif 
}
bool Elysium::Core::operator>=(const String & Left, const String & Right)
{
	if (&Left == &Right)
	{
		return true;
	}

#ifdef UNICODE
	return wcscmp(&Left[0], &Right[0]) >= 0;
#else
	return strcmp(&Left[0], &Right[0]) >= 0;
#endif 
}


const size_t Elysium::Core::String::GetLength() const
{
	return _Length;
}
const ElysiumChar * Elysium::Core::String::GetCharArray() const
{
	return _Data;
}

size_t Elysium::Core::String::IndexOf(const ElysiumChar Value) const
{
#ifdef UNICODE
	size_t Index = wcscspn(_Data, &Value);
#else
	size_t Index = strcspn(_Data, &Value);
#endif

	if (Index >= _Length)
	{
		return std::wstring::npos;
	}
	else
	{
		return Index;
	}
}
size_t Elysium::Core::String::IndexOf(const ElysiumChar Value, const size_t StartIndex) const
{
#ifdef UNICODE
	size_t Index = wcscspn(&_Data[StartIndex], &Value);
#else
	size_t Index = strcspn(&_Data[StartIndex], &Value);
#endif

	if (Index >= _Length - StartIndex)
	{
		return std::wstring::npos;
	}
	else
	{
		return Index;
	}
}
size_t Elysium::Core::String::IndexOf(const ElysiumChar * Value) const
{
#ifdef UNICODE
	ElysiumChar* Result = wcswcs(_Data, Value);
#else
	ElysiumChar* Result = strstr(_Data, Value);
#endif
	if (Result == nullptr)
	{
		return std::wstring::npos;
	}
	else
	{
		return ElysiumStringLength(_Data) - ElysiumStringLength(Result);
	}
}
size_t Elysium::Core::String::IndexOf(const ElysiumChar * Value, const size_t StartIndex) const
{
#ifdef UNICODE
	ElysiumChar* Result = wcswcs(&_Data[StartIndex], Value);
#else
	ElysiumChar* Result = strstr(&_Data[StartIndex], Value);
#endif
	if (Result == nullptr)
	{
		return std::wstring::npos;
	}
	else
	{
		return ElysiumStringLength(&_Data[StartIndex]) - ElysiumStringLength(Result);
	}
}

bool Elysium::Core::String::StartsWith(const ElysiumChar * Value) const
{
	size_t ValueLength = ElysiumStringLength(Value);
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
#ifdef UNICODE
		throw ArgumentNullException(L"Result");
#else
		throw ArgumentNullException("Result");
#endif
	}

	if (Result->_Data != nullptr)
	{
		delete[] Result->_Data;
	}
	Result->_Length = Length;
	Result->_Data = new ElysiumChar[Result->_Length * sizeof(ElysiumChar)];
	memcpy(Result->_Data, &_Data[StartIndex], Length * sizeof(ElysiumChar));
#ifdef UNICODE
	Result->_Data[Result->_Length] = L'\0';
#else
	Result->_Data[Result->_Length] = '\0';
#endif 
}

bool Elysium::Core::String::IsNullOrEmtpy(const String & Value)
{
	return Value._Length == 0;
}
