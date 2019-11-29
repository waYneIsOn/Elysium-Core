#include "StringBuilder.hpp"

#ifndef _XSTRING_
#include <xstring>
#endif

#ifndef __midl
#include <cstring>
#endif

#ifndef ELYSIUM_CORE_EXCEPTION
#include "../Elysium.Core/Exception.hpp"
#endif

#ifndef ELYSIUM_CORE_OUTOFMEMORYEXCEPTION
#include "../Elysium.Core/OutOfMemoryException.hpp"
#endif

Elysium::Core::Text::StringBuilder::StringBuilder()
	: StringBuilder(16)
{
}
Elysium::Core::Text::StringBuilder::StringBuilder(const size_t Capacity)
	: _Capacity(Capacity <= INT_MAX ? Capacity : INT_MAX),
	_Data((char16_t*)malloc(sizeof(char16_t) * _Capacity)),
	_Length(0)
{
}
Elysium::Core::Text::StringBuilder::StringBuilder(const StringBuilder & Source)
	: _Capacity(Source._Capacity),
	_Data(new char16_t[_Capacity]),
	//_Data((char16_t*)malloc(sizeof(char16_t) * _Capacity)),
	_Length(Source._Length)
{
	memcpy(_Data, Source._Data, sizeof(char16_t) * _Capacity);
}
Elysium::Core::Text::StringBuilder::~StringBuilder()
{
	delete[] _Data;
}

const size_t Elysium::Core::Text::StringBuilder::GetCapacity() const
{
	return _Capacity;
}
const size_t Elysium::Core::Text::StringBuilder::GetLength() const
{
	return _Length;
}

void Elysium::Core::Text::StringBuilder::SetLength(const size_t Value)
{
	_Length = Value;
}

void Elysium::Core::Text::StringBuilder::Append(const Elysium::Core::String & Value)
{
	// resize if required
	size_t ValueLength = Value.GetLength();
	Resize(_Length + ValueLength);

	// copy data and set _Length accordingly
	memcpy(&_Data[_Length], &Value[0], sizeof(char16_t) * ValueLength);
	_Length += ValueLength;
}
void Elysium::Core::Text::StringBuilder::Append(const char16_t Value)
{
	Resize(_Length + 1);

	// copy data and set _Length accordingly
	memcpy(&_Data[_Length], &Value, sizeof(char16_t));
	_Length++;
}
void Elysium::Core::Text::StringBuilder::Append(const char16_t * Value, const size_t Length)
{
	// resize if required
	Resize(_Length + Length);

	// copy data and set _Length accordingly
	memcpy(&_Data[_Length], &Value[0], sizeof(char16_t) * Length);
	_Length += Length;
}
void Elysium::Core::Text::StringBuilder::Clear()
{
	_Length = 0;
}
size_t Elysium::Core::Text::StringBuilder::IndexOf(const char16_t Value) const
{
	const char16_t* CharPointer = std::char_traits<char16_t>::find(_Data, _Length, Value);
	return CharPointer == nullptr ? static_cast<const char16_t>(-1) : CharPointer - _Data;
}
size_t Elysium::Core::Text::StringBuilder::IndexOf(const char16_t Value, const size_t StartIndex) const
{
	const char16_t* CharPointer = std::char_traits<char16_t>::find(&_Data[StartIndex], _Length, Value);
	return CharPointer == nullptr ? static_cast<const char16_t>(-1) : CharPointer - &_Data[StartIndex];
}
size_t Elysium::Core::Text::StringBuilder::IndexOf(const char16_t * Value) const
{
	size_t ValueLength = std::char_traits<char16_t>::length(Value);
	for (size_t i = 0; i < _Length; i++)
	{
		if (_Data[i] == Value[0])
		{
			if (i + ValueLength > _Length)
			{
				return static_cast<size_t>(-1);
			}

			bool Found = true;
			for (size_t j = 1; j < ValueLength; j++)
			{
				if (Value[j] != _Data[i++])
				{
					Found = false;
					break;
				}
			}

			if (Found)
			{
				return i;
			}
		}
	}
	return static_cast<size_t>(-1);
	/*
	char16_t* Result = wcswcs(_Data, Value);	// strstr
	if (Result == nullptr)
	{
		return static_cast<const char16_t>(-1);
	}
	else
	{
		return std::char_traits<char16_t>::length(_Data) - std::char_traits<char16_t>::length(Result);
	}
	*/
}
size_t Elysium::Core::Text::StringBuilder::IndexOf(const char16_t * Value, const size_t StartIndex) const
{
	throw Exception(u"not implemented");
	/*
	const char16_t* CharPointer = std::char_traits<char16_t>::find(&_Data[StartIndex], _Length, *Value);
	if (CharPointer == nullptr)
	{
		return static_cast<const char16_t>(-1);
	}
	else
	{
		return CharPointer - &_Data[StartIndex];
	}
	/*
	char16_t* Result = wcswcs(&_Data[StartIndex], Value);	// strstr
	if (Result == nullptr)
	{
		return static_cast<const char16_t>(-1);
	}
	else
	{
		return std::char_traits<char16_t>::length(&_Data[StartIndex]) - std::char_traits<char16_t>::length(Result);
	}
	*/
}
void Elysium::Core::Text::StringBuilder::Remove(const size_t StartIndex, const size_t Length)
{
	// copy data and set _Length accordingly
	memcpy(&_Data[StartIndex], &_Data[Length], sizeof(char16_t) * Length);
	_Length -= Length;
}

Elysium::Core::String Elysium::Core::Text::StringBuilder::ToString()
{
	return String(_Data, _Length);
}
Elysium::Core::String Elysium::Core::Text::StringBuilder::ToString(const size_t Length)
{
	return String(_Data, Length);
}

void Elysium::Core::Text::StringBuilder::Resize(size_t DesiredMinimumSize)
{
	if (DesiredMinimumSize < _Length)
	{	// ToDo: throw a specific ArgumentOutOfRangeException
		throw Exception(u"ArgumentOutOfRangeException");
	}
	if (DesiredMinimumSize > INT_MAX)
	{
		throw OutOfMemoryException();
	}

	if (DesiredMinimumSize > _Capacity)
	{
		// define actual capacity&
		size_t ActualCapacity = _Capacity * 2 + 1;
		while (ActualCapacity < DesiredMinimumSize)
		{
			ActualCapacity = ActualCapacity * 2 + 1;
		}
		if (ActualCapacity > INT_MAX)
		{
			ActualCapacity = INT_MAX;
		}

		// store a pointer to old data before allocating new data
		char16_t* OldData = _Data;
		_Data = (char16_t*)malloc(sizeof(char16_t) * ActualCapacity);
		_Capacity = ActualCapacity;

		// copy all old elements to _Data
		memcpy(&_Data[0], &OldData[0], sizeof(char16_t) * _Length);

		// delete old data
		delete[] OldData;
	}
}
