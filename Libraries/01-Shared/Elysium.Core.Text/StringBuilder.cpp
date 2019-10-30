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
	_Data((ElysiumChar*)malloc(sizeof(ElysiumChar) * _Capacity)),
	_Length(0)
{
}
Elysium::Core::Text::StringBuilder::StringBuilder(const StringBuilder & Source)
	: _Capacity(Source._Capacity),
	_Data((ElysiumChar*)malloc(sizeof(ElysiumChar) * _Capacity)),
	_Length(Source._Length)
{
	memcpy(_Data, Source._Data, sizeof(ElysiumChar) * _Capacity);
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

	// copy data and set _Length accordingly
	memcpy(&_Data[_Length], &Value[0], sizeof(ElysiumChar) * ValueLength);
	_Length += ValueLength;
}
void Elysium::Core::Text::StringBuilder::Append(const ElysiumChar * Value, const size_t Length)
{
	// resize if required
	Resize(_Length + Length);

	// copy data and set _Length accordingly
	memcpy(&_Data[_Length], &Value[0], sizeof(ElysiumChar) * Length);
	_Length += Length;
}
void Elysium::Core::Text::StringBuilder::Clear()
{
	_Length = 0;
}
size_t Elysium::Core::Text::StringBuilder::IndexOf(const ElysiumChar Value) const
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
size_t Elysium::Core::Text::StringBuilder::IndexOf(const ElysiumChar Value, const size_t StartIndex) const
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
size_t Elysium::Core::Text::StringBuilder::IndexOf(const ElysiumChar * Value) const
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
size_t Elysium::Core::Text::StringBuilder::IndexOf(const ElysiumChar * Value, const size_t StartIndex) const
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
void Elysium::Core::Text::StringBuilder::Remove(const size_t StartIndex, const size_t Length)
{
	// copy data and set _Length accordingly
	memcpy(&_Data[StartIndex], &_Data[Length], sizeof(ElysiumChar) * Length);
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
