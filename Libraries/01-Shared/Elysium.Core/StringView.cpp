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
Elysium::Core::StringView::StringView(const Elysium::Core::String * Input)
	: _Data(&Input->operator[](0)), _Length(Input->GetLength())
{
}
Elysium::Core::StringView::StringView(const Elysium::Core::String * Input, size_t Length)
	: _Data(&Input->operator[](0)), _Length(Length)
{
}
Elysium::Core::StringView::StringView(const Elysium::Core::String * Input, size_t Offset, size_t Length)
	: _Data(&Input->operator[](Offset)), _Length(Length)
{
}
Elysium::Core::StringView::StringView(const StringView & Value)
	: _Data(Value._Data), _Length(Value._Length)
{
}
Elysium::Core::StringView::~StringView()
{
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
void Elysium::Core::StringView::Split(const ElysiumChar Delimiter, Elysium::Core::Collections::Generic::List<StringView> * Views) const
{
	size_t DelimiterLength = sizeof(ElysiumChar);
	size_t StartIndex = 0;
	size_t Index = 0;

	do
	{
#ifdef UNICODE
		Index = wcscspn(&_Data[StartIndex], &Delimiter);
#else
		Index = strcspn(&_Data[StartIndex], &Delimiter);
#endif

		Views->Add(StringView(&_Data[StartIndex], Index));
		StartIndex = Index + DelimiterLength;
	} while (Index < _Length);
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

Elysium::Core::StringView & Elysium::Core::StringView::operator=(const StringView & Value)
{
	_Length = Value._Length;
	_Data = Value._Data;
	return *this;
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
