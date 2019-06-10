#include "StringView.hpp"

Elysium::Core::StringView::StringView()
	: _Data(), _Length(0)
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
