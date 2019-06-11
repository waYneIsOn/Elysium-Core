#include "StringView.hpp"

#ifndef _XSTRING_
#include <xstring>
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

void Elysium::Core::StringView::Split(const ElysiumChar Delimiter, Elysium::Core::Collections::Generic::List<StringView> * Views)
{
	throw NotImplementedException();
	/*
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
	} while (Index != std::wstring::npos);
	*/
}
void Elysium::Core::StringView::Split(const ElysiumChar* Delimiter, Elysium::Core::Collections::Generic::List<StringView>* Views)
{
	size_t DelimiterLength = ElysiumStringLength(Delimiter);
	size_t StartIndex = 0;
	size_t Length = 0;
	ElysiumChar* Result = nullptr;

	int i = 0;
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

		//Views->operator[](i)._Data = &_Data[StartIndex];
		//Views->operator[](i)._Length = Length;
		Views->Add(StringView(&_Data[StartIndex], Length));
		StartIndex += Length + DelimiterLength;

		//String Test = Views->operator[](i);
		i++;
	} while (Result != nullptr);
}

Elysium::Core::StringView & Elysium::Core::StringView::operator=(const StringView & Value)
{
	_Length = Value._Length;
	_Data = Value._Data;
	return *this;
}

Elysium::Core::StringView::operator Elysium::Core::String() const
{
	return String(_Data, _Length);
}
