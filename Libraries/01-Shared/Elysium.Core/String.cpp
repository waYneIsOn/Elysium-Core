#include "String.hpp"

#ifndef ELYSIUM_CORE_MEMORY
#include "Memory.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LIST
#include "List.hpp"
#endif

#ifndef ELYSIUM_CORE_INDEXOUTOFRANGEEXCEPTION
#include "IndexOutOfRangeException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CHARACTERTRAITS
#include "../Elysium.Core.Template/CharacterTraits.hpp"
#endif

const Elysium::Core::Utf8String Elysium::Core::Utf8String::Empty = Elysium::Core::Utf8String();

Elysium::Core::Utf8String::Utf8String()
	: _Length(0), _Data(nullptr)
{ }

Elysium::Core::Utf8String::Utf8String(const Elysium::Core::size Length)
	: _Length(Length), _Data(new char8_t[_Length + 1])
{
	Elysium::Core::Memory<char8_t>::Set(_Data, 0, _Length + 1);
}

Elysium::Core::Utf8String::Utf8String(ConstCharacterPointer Value)
	: _Length(Value == nullptr ? 0 : Elysium::Core::Template::Text::CharacterTraits<char8_t>::GetLength(Value)), _Data(_Length == 0 ? nullptr : new char8_t[_Length + 1])
{
	if (_Data != nullptr)
	{
		Elysium::Core::Memory<char8_t>::Copy(_Data, Value, _Length + 1);
	}
}

Elysium::Core::Utf8String::Utf8String(ConstCharacterPointer Value, const Elysium::Core::size Length)
	: _Length(Value == nullptr ? 0 : Length), _Data(_Length == 0 ? nullptr : new char8_t[_Length + 1])
{
	if (_Data != nullptr)
	{
		Elysium::Core::Memory<char8_t>::Copy(_Data, Value, _Length);
		_Data[_Length] = Elysium::Core::Template::Text::CharacterTraits<Character>::NullTerminationCharacter;
	}
}

Elysium::Core::Utf8String::Utf8String(const Utf8String& Source)
	: _Length(Source._Length), _Data(_Length == 0 ? nullptr : new char8_t[_Length + 1])
{
	if (_Data != nullptr)
	{
		Elysium::Core::Memory<char8_t>::Copy(_Data, Source._Data, _Length + 1);
	}
}

Elysium::Core::Utf8String::Utf8String(Utf8String&& Right) noexcept
	: _Length(0), _Data(nullptr)
{
	*this = Elysium::Core::Template::Functional::Move(Right);
}

Elysium::Core::Utf8String::~Utf8String()
{
	if (_Data != nullptr)
	{
		delete[] _Data;
		_Data = nullptr;
	}
}

Elysium::Core::Utf8String& Elysium::Core::Utf8String::operator=(ConstCharacterPointer Value)
{
	if (_Data != nullptr)
	{
		delete[] _Data;
	}

	_Length = Value == nullptr ? 0 : Elysium::Core::Template::Text::CharacterTraits<char8_t>::GetLength(Value);
	_Data = _Length == 0 ? nullptr : new char8_t[_Length + 1];
	if (_Data != nullptr)
	{
		memcpy(_Data, Value, (_Length + 1) * sizeof(char8_t));
	}
	return *this;
}

Elysium::Core::Utf8String& Elysium::Core::Utf8String::operator=(const Utf8String& Source)
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

Elysium::Core::Utf8String& Elysium::Core::Utf8String::operator=(Elysium::Core::Utf8String&& Right) noexcept
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

const bool Elysium::Core::Utf8String::operator==(const Utf8String& Other) const
{
	if (this == &Other)
	{
		return true;
	}
	return Elysium::Core::Template::Text::CharacterTraits<char8_t>::Compare(_Data, Other._Data, Other._Length) == 0;
}

const bool Elysium::Core::Utf8String::operator!=(const Utf8String& Other) const
{
	if (this == &Other)
	{
		return false;
	}
	return Elysium::Core::Template::Text::CharacterTraits<char8_t>::Compare(_Data, Other._Data, Other._Length) != 0;
}

const bool Elysium::Core::Utf8String::operator<(const Utf8String& Other) const
{
	if (this == &Other)
	{
		return false;
	}
	return Elysium::Core::Template::Text::CharacterTraits<char8_t>::Compare(_Data, Other._Data, Other._Length) < 0;
}

const bool Elysium::Core::Utf8String::operator>(const Utf8String& Other) const
{
	if (this == &Other)
	{
		return false;
	}
	return Elysium::Core::Template::Text::CharacterTraits<char8_t>::Compare(_Data, Other._Data, Other._Length) > 0;
}

const bool Elysium::Core::Utf8String::operator<=(const Utf8String Other) const
{
	if (this == &Other)
	{
		return true;
	}
	return Elysium::Core::Template::Text::CharacterTraits<char8_t>::Compare(_Data, Other._Data, Other._Length) <= 0;
}

const bool Elysium::Core::Utf8String::operator>=(const Utf8String& Other) const
{
	if (this == &Other)
	{
		return true;
	}
	return Elysium::Core::Template::Text::CharacterTraits<char8_t>::Compare(_Data, Other._Data, Other._Length) >= 0;
}

const bool Elysium::Core::Utf8String::operator==(const char8_t* Other) const
{
	return Elysium::Core::Template::Text::CharacterTraits<char8_t>::Compare(_Data, Other, Elysium::Core::Template::Text::CharacterTraits<char8_t>::GetLength(Other)) == 0;
}

const bool Elysium::Core::Utf8String::operator!=(const char8_t* Other) const
{
	return Elysium::Core::Template::Text::CharacterTraits<char8_t>::Compare(_Data, Other, Elysium::Core::Template::Text::CharacterTraits<char8_t>::GetLength(Other)) != 0;
}

Elysium::Core::Utf8String::CharacterReference Elysium::Core::Utf8String::operator[](const Elysium::Core::size Index)
{
	if (Index >= _Length)
	{
		throw IndexOutOfRangeException();
	}
	return _Data[Index];
}

Elysium::Core::Utf8String::ConstCharacterReference Elysium::Core::Utf8String::operator[](const Elysium::Core::size Index) const
{
	if (Index >= _Length)
	{
		throw IndexOutOfRangeException();
	}
	return _Data[Index];
}

Elysium::Core::size Elysium::Core::Utf8String::GetHashCode() const
{	// code below should work similar to std::hash<std::u8string>()(_Data);
	Elysium::Core::size Hash = 14695981039346656037ULL;
	if (_Length == 0)
	{
		return Hash;
	}
	CharacterPointer CurrentChar = &_Data[0];
	while (*CurrentChar != Elysium::Core::Template::Text::CharacterTraits<Character>::NullTerminationCharacter)
	{
		Hash ^= static_cast<Elysium::Core::size>(*CurrentChar);
		Hash *= 1099511628211ULL;
		CurrentChar++;
	}

	return Hash;
}

const Elysium::Core::size Elysium::Core::Utf8String::GetLength() const
{
	return _Length;
}

const Elysium::Core::size Elysium::Core::Utf8String::IndexOf(ConstCharacter Value) const
{
	const char8_t* CharPointer = Elysium::Core::Template::Text::CharacterTraits<char8_t>::Find(_Data, _Length, Value);
	return CharPointer == nullptr ? static_cast<Elysium::Core::size>(-1) : CharPointer - _Data;
}

const Elysium::Core::size Elysium::Core::Utf8String::IndexOf(ConstCharacter Value, const Elysium::Core::size StartIndex) const
{
	const char8_t* CharPointer = Elysium::Core::Template::Text::CharacterTraits<char8_t>::Find(&_Data[StartIndex], _Length - StartIndex, Value);
	return CharPointer == nullptr ? static_cast<Elysium::Core::size>(-1) : CharPointer - &_Data[StartIndex];
}

const Elysium::Core::size Elysium::Core::Utf8String::IndexOf(ConstCharacterPointer Value) const
{
	Elysium::Core::size Index = 0;
	Elysium::Core::size SizeOfValue = Elysium::Core::Template::Text::CharacterTraits<char8_t>::GetLength(Value);
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

const Elysium::Core::size Elysium::Core::Utf8String::IndexOf(ConstCharacterPointer Value, const Elysium::Core::size StartIndex) const
{
	Elysium::Core::size Index = StartIndex;
	Elysium::Core::size SizeOfValue = Elysium::Core::Template::Text::CharacterTraits<char8_t>::GetLength(Value);
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

const Elysium::Core::size Elysium::Core::Utf8String::IndexOf(const Elysium::Core::Utf8String& Value, const Elysium::Core::size StartIndex) const
{
	return IndexOf(Value._Data[StartIndex]);
}

const Elysium::Core::size Elysium::Core::Utf8String::LastIndexOf(ConstCharacter Value) const
{
	char8_t* CharPointer = nullptr;
	for (Elysium::Core::size i = _Length; i > 0; i--)
	{
		if (_Data[i - 1] == Value)
		{
			CharPointer = &_Data[i - 1];
			break;
		}
	}
	return CharPointer == nullptr ? static_cast<Elysium::Core::size>(-1) : CharPointer - _Data;
}

const Elysium::Core::size Elysium::Core::Utf8String::LastIndexOf(ConstCharacterPointer Value) const
{
	// ToDo
	return Elysium::Core::size(-1);
}

const Elysium::Core::size Elysium::Core::Utf8String::LastIndexOf(ConstCharacterPointer Value, const Elysium::Core::size StartIndex) const
{	// ToDo
	return Elysium::Core::size(-1);
}

const Elysium::Core::size Elysium::Core::Utf8String::LastIndexOf(const Utf8String& Value, const Elysium::Core::size StartIndex) const
{	// ToDo
	return Elysium::Core::size(-1);
}

void Elysium::Core::Utf8String::Split(ConstCharacter Delimiter, Collections::Template::List<Utf8String>& Target) const
{
	Elysium::Core::size StartIndex = 0;
	Elysium::Core::size Length = 0;

	while (true)
	{
		Length = IndexOf(Delimiter, StartIndex);
		if (Length == static_cast<Elysium::Core::size>(-1))
		{
			if (_Length - StartIndex > 0)
			{
				Target.Add(Utf8String(&_Data[StartIndex], _Length - StartIndex));
			}
			break;
		}
		Target.Add(Utf8String(&_Data[StartIndex], Length));
		StartIndex += Length + 1;
	}
}

void Elysium::Core::Utf8String::Split(ConstCharacterPointer Delimiter, Collections::Template::List<Utf8String>& Target) const
{
	Elysium::Core::size DelimiterLength = Elysium::Core::Template::Text::CharacterTraits<char8_t>::GetLength(Delimiter);
	Elysium::Core::size StartIndex = 0;
	Elysium::Core::size Length = 0;

	while (true)
	{
		Length = IndexOf(Delimiter, StartIndex);
		if (Length == static_cast<Elysium::Core::size>(-1))
		{
			if (_Length - StartIndex > 0)
			{
				Target.Add(Utf8String(&_Data[StartIndex], _Length - StartIndex));
			}
			break;
		}
		Target.Add(Utf8String(&_Data[StartIndex], Length - StartIndex));
		StartIndex += (Length - StartIndex) + DelimiterLength;
	}
}

const bool Elysium::Core::Utf8String::StartsWith(ConstCharacterPointer Value) const
{
	Elysium::Core::size ValueLength = Elysium::Core::Template::Text::CharacterTraits<char8_t>::GetLength(Value);
	for (Elysium::Core::size i = 0; i < ValueLength; i++)
	{
		if (_Data[i] != Value[i])
		{
			return false;
		}
	}
	return true;
}

const bool Elysium::Core::Utf8String::EndsWith(ConstCharacterPointer Value) const
{
	Elysium::Core::size ValueLength = Elysium::Core::Template::Text::CharacterTraits<char8_t>::GetLength(Value);
	for (Elysium::Core::size i = _Length - ValueLength; i < _Length; i++)
	{
		if (_Data[i] != Value[_Length - 1 - i])
		{
			return false;
		}
	}
	return true;
}

Elysium::Core::Utf8String Elysium::Core::Utf8String::Substring(const Elysium::Core::size StartIndex) const
{
	return Utf8String(&_Data[StartIndex], _Length - StartIndex);
}

Elysium::Core::Utf8String Elysium::Core::Utf8String::Substring(const Elysium::Core::size StartIndex, const Elysium::Core::size Length) const
{
	return Utf8String(&_Data[StartIndex], Length);
}

const bool Elysium::Core::Utf8String::IsNull(const Utf8String& Value)
{
	return Value._Data == nullptr;
}

const bool Elysium::Core::Utf8String::IsEmpty(const Utf8String& Value)
{
	return Value._Data != nullptr && Value._Length == 1;
}

const bool Elysium::Core::Utf8String::IsNullOrEmtpy(const Utf8String& Value)
{
	return Value._Data == nullptr || (Value._Data != nullptr && Value._Length == 1);
}
