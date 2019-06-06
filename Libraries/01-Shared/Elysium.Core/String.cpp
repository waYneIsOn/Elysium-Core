#include "String.hpp"

#ifndef _INC_STRING
#include <string>
#endif

#ifdef UNICODE
#define ElysiumStringLength wcslen
#else
#define ElysiumStringLength strlen
#endif 

#ifndef ELYSIUM_CORE_INDEXOUTOFRANGEEXCEPTION
#include "IndexOutOfRangeException.hpp"
#endif

#ifndef ELYSIUM_CORE_ARGUMENTNULLEXCEPTION
#include "ArgumentNullException.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "NotImplementedException.hpp"
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
Elysium::Core::String::String(const String & Value)
	: Elysium::Core::String(Value._Length)
{
	memcpy(_Data, Value._Data, _Length * sizeof(ElysiumChar));
#ifdef UNICODE
	_Data[_Length] = L'\0';
#else
	_Data[_Length] = '\0';
#endif 
}
Elysium::Core::String::~String()
{
	if (_Data != nullptr)
	{
		delete[] _Data;
	}
}

const size_t Elysium::Core::String::GetLength() const
{
	return _Length;
}
const ElysiumChar * Elysium::Core::String::GetCharArray() const
{
	return _Data;
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
Elysium::Core::String & Elysium::Core::String::operator=(const String & Value)
{
	if (&Value != this)
	{
		if (_Data != nullptr)
		{
			delete[] _Data;
		}
		_Length = Value._Length;
		_Data = new ElysiumChar[_Length + sizeof(ElysiumChar)];
		memcpy(_Data, Value._Data, _Length * sizeof(ElysiumChar));
#ifdef UNICODE
		_Data[_Length] = L'\0';
#else
		_Data[_Length] = '\0';
#endif 
	}

	return *this;
}

ElysiumChar & Elysium::Core::String::operator[](size_t Index) const
{
	if (Index >= _Length)
	{
		throw IndexOutOfRangeException();
	}

	return _Data[Index];
}

bool Elysium::Core::String::operator<(const String & Other)
{
	throw NotImplementedException();
}

bool Elysium::Core::String::IsNullOrEmtpy(const String & Value)
{
	return Value._Length == 0;
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
