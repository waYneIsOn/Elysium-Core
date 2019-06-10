#include "StringBuilder.hpp"

#ifndef __midl
#include <cstring>
#endif

#ifndef _INC_LIMITS
#include <limits>
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
	_Data((ElysiumChar*)malloc(sizeof(ElysiumChar) * _Capacity)),
	_Length(0)
{
}
Elysium::Core::Text::StringBuilder::StringBuilder(const StringBuilder & Value)
	: _Capacity(Value._Capacity),
	_Data((ElysiumChar*)malloc(sizeof(ElysiumChar) * _Capacity)),
	_Length(Value._Length)
{
	memcpy(_Data, Value._Data, sizeof(ElysiumChar) * _Capacity);
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

	// copy data and set _NumberOfElements accordingly
	memcpy(&_Data[_Length], &Value[0], sizeof(ElysiumChar) * ValueLength);
	_Length += ValueLength;
}
void Elysium::Core::Text::StringBuilder::Append(const ElysiumChar * Value)
{
	// resize if required
#ifdef UNICODE
	size_t ValueLength = wcslen(Value);
#else
	size_t ValueLength = strlen(Value);
#endif 
	Resize(_Length + ValueLength);

	// copy data and set _NumberOfElements accordingly
	memcpy(&_Data[_Length], &Value[0], sizeof(ElysiumChar) * ValueLength);
	_Length += ValueLength;
}

void Elysium::Core::Text::StringBuilder::ToString(Elysium::Core::String * Output)
{
	*Output = String(_Data, _Length);
}

void Elysium::Core::Text::StringBuilder::Resize(size_t DesiredMinimumSize)
{
	if (DesiredMinimumSize < _Length)
	{	// ToDo: throw a specific ArgumentOutOfRangeException
#ifdef UNICODE
		throw Exception(L"ArgumentOutOfRangeException");
#else
		throw Exception("ArgumentOutOfRangeException");
#endif
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
		ElysiumChar* OldData = _Data;
		_Data = (ElysiumChar*)malloc(sizeof(ElysiumChar) * ActualCapacity);
		_Capacity = ActualCapacity;

		// copy all old elements to _Data
		memcpy(&_Data[0], &OldData[0], sizeof(ElysiumChar) * _Length);

		// delete old data
		delete[] OldData;
	}
}
