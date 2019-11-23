#include "StringView.hpp"

#ifndef _XSTRING_
#include <xstring>
#endif

#ifndef ELYSIUM_CORE_INDEXOUTOFRANGEEXCEPTION
#include "IndexOutOfRangeException.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "NotImplementedException.hpp"
#endif

Elysium::Core::StringView::StringView()
	: _Data(nullptr), _Length(0)
{
}
Elysium::Core::StringView::StringView(ElysiumChar * Input)
	: _Data(&Input[0]), _Length(ElysiumStringLength(Input))
{
}
Elysium::Core::StringView::StringView(ElysiumChar * Input, size_t Length)
	: _Data(&Input[0]), _Length(Length)
{
}
Elysium::Core::StringView::StringView(const Elysium::Core::String & Input)
	: _Data(&Input[0]), _Length(Input.GetLength())
{
}
Elysium::Core::StringView::StringView(const Elysium::Core::String & Input, size_t Length)
	: _Data(&Input[0]), _Length(Length)
{
}
Elysium::Core::StringView::StringView(const Elysium::Core::String & Input, size_t Offset, size_t Length)
	: _Data(&Input[Offset]), _Length(Length)
{
}
Elysium::Core::StringView::StringView(const StringView & Source)
	: _Data(Source._Data), _Length(Source._Length)
{
}
Elysium::Core::StringView::StringView(StringView && Right) noexcept
{
	*this = std::move(Right);
}
Elysium::Core::StringView::~StringView()
{
}

Elysium::Core::StringView & Elysium::Core::StringView::operator=(const StringView & Value)
{
	_Length = Value._Length;
	_Data = Value._Data;
	return *this;
}
Elysium::Core::StringView & Elysium::Core::StringView::operator=(StringView && Right) noexcept
{
	if (this != &Right)
	{
		// grab Right's objects
		_Data = Right._Data;
		_Length = Right._Length;

		// release Right's objects
		Right._Data = nullptr;
		Right._Length = 0;
	}

	return *this;
}

bool Elysium::Core::StringView::operator==(const StringView & Other) const
{
	if (this == &Other)
	{
		return true;
	}

	return _Data == Other._Data && _Length == Other._Length;
}
bool Elysium::Core::StringView::operator!=(const StringView & Other) const
{
	if (this == &Other)
	{
		return false;
	}

	return _Data != Other._Data || _Length != Other._Length;
}
bool Elysium::Core::StringView::operator<(const StringView & Other) const
{
	return _Data == Other._Data && _Length < Other._Length;
}
bool Elysium::Core::StringView::operator>(const StringView & Other) const
{
	return _Data == Other._Data && _Length > Other._Length;
}
bool Elysium::Core::StringView::operator<=(const StringView & Other) const
{
	if (this == &Other)
	{
		return true;
	}

	return _Data == Other._Data && _Length <= Other._Length;
}
bool Elysium::Core::StringView::operator>=(const StringView & Other) const
{
	if (this == &Other)
	{
		return true;
	}

	return _Data == Other._Data && _Length >= Other._Length;
}

const size_t Elysium::Core::StringView::GetLength() const
{
	return _Length;
}

size_t Elysium::Core::StringView::IndexOf(const ElysiumChar Value) const
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
size_t Elysium::Core::StringView::IndexOf(const ElysiumChar Value, const size_t StartIndex) const
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
size_t Elysium::Core::StringView::IndexOf(const ElysiumChar * Value) const
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
size_t Elysium::Core::StringView::IndexOf(const ElysiumChar * Value, const size_t StartIndex) const
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
size_t Elysium::Core::StringView::IndexOf(const String & Value, const size_t StartIndex) const
{
	return IndexOf(Value[StartIndex]);
}
void Elysium::Core::StringView::Split(const ElysiumChar Delimiter, Elysium::Core::Collections::Generic::List<StringView> * Views) const
{
	size_t StartIndex = 0;
	size_t Length = 0;

	do
	{
#ifdef UNICODE
		Length = wcscspn(&_Data[StartIndex], &Delimiter);
#else
		Length = strcspn(&_Data[StartIndex], &Delimiter);
#endif

		Views->Add(StringView(&_Data[StartIndex], Length));
		StartIndex = Length + 1;
	} while (Length < _Length);
}
void Elysium::Core::StringView::Split(const ElysiumChar* Delimiter, Elysium::Core::Collections::Generic::List<StringView>* Views) const
{
	size_t DelimiterLength = ElysiumStringLength(Delimiter);
	size_t StartIndex = 0;
	size_t Length = 0;
	ElysiumChar* Result = nullptr;

	do
	{
#ifdef UNICODE
		Result = wcswcs(&_Data[StartIndex], Delimiter);
#else
		Result = strstr(&_Data[StartIndex], Delimiter);
#endif
		
		if (Result == nullptr)
		{
			Length = ElysiumStringLength(&_Data[StartIndex]);
		}
		else
		{
			Length = ElysiumStringLength(&_Data[StartIndex]) - ElysiumStringLength(Result);
		}

		Views->Add(StringView(&_Data[StartIndex], Length));
		StartIndex += Length + DelimiterLength;
	} while (Result != nullptr);
}

ElysiumChar & Elysium::Core::StringView::operator[](size_t Index) const
{
	if (Index > _Length)	// not >= because or \0
	{
		throw IndexOutOfRangeException();
	}

	return _Data[Index];
}

Elysium::Core::StringView::operator Elysium::Core::String() const
{
	return String(_Data, _Length);
}
