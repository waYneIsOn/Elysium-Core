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

Elysium::Core::String::String(const ElysiumChar* Value)
	: Elysium::Core::String(Value == nullptr ? 0 : ElysiumStringLength(Value))
{
	memcpy(_Data, Value, _Length * sizeof(ElysiumChar));
}
Elysium::Core::String::String(const ElysiumChar * Value, size_t Length)
	: Elysium::Core::String(Value == nullptr ? 0 : Length)
{
	memcpy(_Data, Value, _Length * sizeof(ElysiumChar));
}
Elysium::Core::String::String(const String & Value)
	: Elysium::Core::String(Value._Length)
{
	memcpy(_Data, Value._Data, _Length * sizeof(ElysiumChar));
}
Elysium::Core::String::~String()
{
	delete[] _Data;
}

const size_t Elysium::Core::String::GetLength() const
{
	return _Length;
}

ElysiumChar & Elysium::Core::String::operator[](size_t Index) const
{
	if (Index >= _Length)
	{
		throw IndexOutOfRangeException();
	}

	return _Data[Index];
}

bool Elysium::Core::String::IsNullOrEmtpy(const String & Value)
{
	return Value._Length == 0;
}

const ElysiumChar * Elysium::Core::String::ToCharArray() const
{
	return _Data;
}

Elysium::Core::String::String(size_t Length)
	: _Length(Length), _Data(new ElysiumChar[_Length])
{
}
