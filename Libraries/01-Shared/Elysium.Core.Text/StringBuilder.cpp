#include "StringBuilder.hpp"

#ifndef __midl
#include <cstring>
#endif

#ifndef ELYSIUM_CORE_EXCEPTION
#include "../Elysium.Core/Exception.hpp"
#endif

#ifndef ELYSIUM_CORE_OUTOFMEMORYEXCEPTION
#include "../Elysium.Core/OutOfMemoryException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NUMERIC_NUMERICLIMITS
#include "../Elysium.Core.Template/NumericLimits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRINGTRAITS
#include "../Elysium.Core.Template/StringTraits.hpp"
#endif

Elysium::Core::Text::StringBuilder::StringBuilder()
	: StringBuilder(16)
{ }
Elysium::Core::Text::StringBuilder::StringBuilder(const Elysium::Core::size Capacity)
	: _Capacity(Capacity <= Elysium::Core::Template::Numeric::NumericLimits<Elysium::Core::int32_t>::Maximum ? Capacity : Elysium::Core::Template::Numeric::NumericLimits<Elysium::Core::int32_t>::Maximum),
	_Data(new char8_t[_Capacity]),
	_Length(0)
{ }
Elysium::Core::Text::StringBuilder::StringBuilder(const StringBuilder & Source)
	: _Capacity(Source._Capacity),_Data(new char8_t[_Capacity]), _Length(Source._Length)
{
	memcpy(_Data, Source._Data, sizeof(char8_t) * _Capacity);
}
Elysium::Core::Text::StringBuilder::~StringBuilder()
{
	if (_Data != nullptr)
	{
		delete[] _Data;
		_Data = nullptr;
	}
}

const Elysium::Core::size Elysium::Core::Text::StringBuilder::GetCapacity() const
{
	return _Capacity;
}
const Elysium::Core::size Elysium::Core::Text::StringBuilder::GetLength() const
{
	return _Length;
}

void Elysium::Core::Text::StringBuilder::SetLength(const Elysium::Core::size Value)
{
	_Length = Value;
}

void Elysium::Core::Text::StringBuilder::Append(const Elysium::Core::String & Value)
{
	// resize if required
	Elysium::Core::size ValueLength = Value.GetLength();
	Resize(_Length + ValueLength);

	// copy data and set _Length accordingly
	memcpy(&_Data[_Length], &Value[0], sizeof(char8_t) * ValueLength);
	_Length += ValueLength;
}
void Elysium::Core::Text::StringBuilder::Append(const char8_t Value)
{
	Resize(_Length + 1);

	// copy data and set _Length accordingly
	memcpy(&_Data[_Length], &Value, sizeof(char8_t));
	_Length++;
}
void Elysium::Core::Text::StringBuilder::Append(const char8_t * Value, const Elysium::Core::size Length)
{
	// resize if required
	Resize(_Length + Length);

	// copy data and set _Length accordingly
	memcpy(&_Data[_Length], &Value[0], sizeof(char8_t) * Length);
	_Length += Length;
}
void Elysium::Core::Text::StringBuilder::Clear()
{
	_Length = 0;
}
Elysium::Core::size Elysium::Core::Text::StringBuilder::IndexOf(const char8_t Value) const
{
	const char8_t* CharPointer = Elysium::Core::Template::Text::StringTraits<char8_t>::Find(_Data, _Length, Value);
	return CharPointer == nullptr ? static_cast<const char8_t>(-1) : CharPointer - _Data;
}
Elysium::Core::size Elysium::Core::Text::StringBuilder::IndexOf(const char8_t Value, const Elysium::Core::size StartIndex) const
{
	const char8_t* CharPointer = Elysium::Core::Template::Text::StringTraits<char8_t>::Find(&_Data[StartIndex], _Length - StartIndex, Value);
	return CharPointer == nullptr ? static_cast<Elysium::Core::size>(-1) : CharPointer - &_Data[StartIndex];
}
Elysium::Core::size Elysium::Core::Text::StringBuilder::IndexOf(const char8_t * Value) const
{
	Elysium::Core::size Index = 0;
	Elysium::Core::size SizeOfValue = Elysium::Core::Template::Text::StringTraits<char8_t>::GetLength(Value);
	while (true)
	{
		Elysium::Core::size CurrentIndex = IndexOf(Value[0], Index);
		if (CurrentIndex == static_cast<Elysium::Core::size>(-1))
		{
			return CurrentIndex;
		}

		Index += CurrentIndex;
		if (Index + SizeOfValue > _Length)
		{
			return static_cast<Elysium::Core::size>(-1);
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
Elysium::Core::size Elysium::Core::Text::StringBuilder::IndexOf(const char8_t * Value, const Elysium::Core::size StartIndex) const
{
	Elysium::Core::size Index = StartIndex;
	Elysium::Core::size SizeOfValue = Elysium::Core::Template::Text::StringTraits<char8_t>::GetLength(Value);
	while (true)
	{
		Elysium::Core::size CurrentIndex = IndexOf(Value[0], Index);
		if (CurrentIndex == static_cast<Elysium::Core::size>(-1))
		{
			return CurrentIndex;
		}

		Index += CurrentIndex;
		if (Index + SizeOfValue > _Length)
		{
			return static_cast<Elysium::Core::size>(-1);
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
void Elysium::Core::Text::StringBuilder::Remove(const Elysium::Core::size StartIndex, const Elysium::Core::size Length)
{
	// copy data and set _Length accordingly
	memcpy(&_Data[StartIndex], &_Data[Length], sizeof(char8_t) * Length);
	_Length -= Length;
}

Elysium::Core::String Elysium::Core::Text::StringBuilder::ToString()
{
	return String(_Data, _Length);
}
Elysium::Core::String Elysium::Core::Text::StringBuilder::ToString(const Elysium::Core::size Length)
{
	return String(_Data, Length);
}

void Elysium::Core::Text::StringBuilder::Resize(Elysium::Core::size DesiredMinimumSize)
{
	if (DesiredMinimumSize < _Length)
	{	// ToDo: throw a specific ArgumentOutOfRangeException
		throw Exception(u8"ArgumentOutOfRangeException");
	}
	if (DesiredMinimumSize > Elysium::Core::Template::Numeric::NumericLimits<Elysium::Core::int32_t>::Maximum)
	{
		throw OutOfMemoryException();
	}

	if (DesiredMinimumSize > _Capacity)
	{
		// define actual capacity&
		Elysium::Core::size ActualCapacity = _Capacity * 2 + 1;
		while (ActualCapacity < DesiredMinimumSize)
		{
			ActualCapacity = ActualCapacity * 2 + 1;
		}
		if (ActualCapacity > Elysium::Core::Template::Numeric::NumericLimits<Elysium::Core::int32_t>::Maximum)
		{
			ActualCapacity = Elysium::Core::Template::Numeric::NumericLimits<Elysium::Core::int32_t>::Maximum;
		}

		// store a pointer to old data before allocating new data
		char8_t* OldData = _Data;
		_Data = new char8_t[ActualCapacity];
		if (_Data == nullptr)
		{	// ToDo: throw specific exception (OutOfMemoryException?)
			throw 1;
		}
		_Capacity = ActualCapacity;

		// copy all old elements to _Data
		memcpy(_Data, OldData, sizeof(char8_t) * _Length);

		// delete old data
		delete[] OldData;
	}
}
