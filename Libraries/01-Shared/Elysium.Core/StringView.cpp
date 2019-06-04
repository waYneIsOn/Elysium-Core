#include "StringView.hpp"

Elysium::Core::StringView::StringView()
	: _Data(), _Length(0)
{
}
Elysium::Core::StringView::StringView(const String & Input, size_t Length)
	: _Data(Input.GetCharArray()), _Length(Length)
{
}
Elysium::Core::StringView::~StringView()
{
}

const ElysiumChar * Elysium::Core::StringView::GetData() const
{
	return _Data;
}
const size_t Elysium::Core::StringView::GetLength() const
{
	return _Length;
}