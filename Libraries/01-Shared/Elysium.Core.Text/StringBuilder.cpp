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
{ }
Elysium::Core::Text::StringBuilder::StringBuilder(const size_t Capacity)
	: _Capacity(Capacity <= INT_MAX ? Capacity : INT_MAX),
	_Data((char*)malloc(sizeof(char) * _Capacity)),
	_Length(0)
{ }
Elysium::Core::Text::StringBuilder::StringBuilder(const StringBuilder & Source)
	: _Capacity(Source._Capacity),
	_Data(new char[_Capacity]),
	//_Data((char16_t*)malloc(sizeof(char16_t) * _Capacity)),
	_Length(Source._Length)
{
	memcpy(_Data, Source._Data, sizeof(char) * _Capacity);
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
	memcpy(&_Data[_Length], &Value[0], sizeof(char) * ValueLength);
	_Length += ValueLength;
}
void Elysium::Core::Text::StringBuilder::Append(const char Value)
{
	Resize(_Length + 1);

	// copy data and set _Length accordingly
	memcpy(&_Data[_Length], &Value, sizeof(char));
	_Length++;
}
void Elysium::Core::Text::StringBuilder::Append(const char * Value, const size_t Length)
{
	// resize if required
	Resize(_Length + Length);

	// copy data and set _Length accordingly
	memcpy(&_Data[_Length], &Value[0], sizeof(char) * Length);
	_Length += Length;
}
void Elysium::Core::Text::StringBuilder::Clear()
{
	_Length = 0;
}
size_t Elysium::Core::Text::StringBuilder::IndexOf(const char Value) const
{
	const char* CharPointer = std::char_traits<char>::find(_Data, _Length, Value);
	return CharPointer == nullptr ? static_cast<const char>(-1) : CharPointer - _Data;
}
size_t Elysium::Core::Text::StringBuilder::IndexOf(const char Value, const size_t StartIndex) const
{
	const char* CharPointer = std::char_traits<char>::find(&_Data[StartIndex], _Length - StartIndex, Value);
	return CharPointer == nullptr ? static_cast<size_t>(-1) : CharPointer - &_Data[StartIndex];
}
size_t Elysium::Core::Text::StringBuilder::IndexOf(const char * Value) const
{
	size_t Index = 0;
	size_t SizeOfValue = std::char_traits<char>::length(Value);
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
size_t Elysium::Core::Text::StringBuilder::IndexOf(const char * Value, const size_t StartIndex) const
{
	size_t Index = StartIndex;
	size_t SizeOfValue = std::char_traits<char>::length(Value);
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
		throw Exception(u8"ArgumentOutOfRangeException");
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
		char* OldData = _Data;
		_Data = (char*)malloc(sizeof(char) * ActualCapacity);
		_Capacity = ActualCapacity;

		// copy all old elements to _Data
		memcpy(&_Data[0], &OldData[0], sizeof(char) * _Length);

		// delete old data
		delete[] OldData;
	}
}
