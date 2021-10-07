#include "DateTimeOffset.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::DateTimeOffset::DateTimeOffset(const DateTime DateTime)
	: Elysium::Core::DateTimeOffset::DateTimeOffset(DateTime, TimeSpan::Zero())
{ }
Elysium::Core::DateTimeOffset::DateTimeOffset(const DateTime DateTime, const TimeSpan Offset)
	: _DateTime(DateTime), _Offset(Offset)
{ }
Elysium::Core::DateTimeOffset::DateTimeOffset(const DateTimeOffset & Source)
	: _DateTime(DateTime(Source._DateTime)), _Offset(TimeSpan(Source._Offset))
{ }
Elysium::Core::DateTimeOffset::DateTimeOffset(DateTimeOffset && Right) noexcept
	: _DateTime(0), _Offset(0)
{
	*this = Elysium::Core::Template::Functional::Move(Right);
}
Elysium::Core::DateTimeOffset::~DateTimeOffset()
{ }

Elysium::Core::DateTimeOffset & Elysium::Core::DateTimeOffset::operator=(const DateTimeOffset & Source)
{
	if (this != &Source)
	{
		_DateTime = DateTime(Source._DateTime);
		_Offset = TimeSpan(Source._Offset);
	}
	return *this;
}
Elysium::Core::DateTimeOffset & Elysium::Core::DateTimeOffset::operator=(DateTimeOffset && Right) noexcept
{
	if (this != &Right)
	{
		_DateTime = Elysium::Core::Template::Functional::Move(Right._DateTime);
		_Offset = Elysium::Core::Template::Functional::Move(Right._Offset);
	}
	return *this;
}

Elysium::Core::DateTime & Elysium::Core::DateTimeOffset::GetDateTime() const
{
	return (DateTime&)_DateTime;
}

Elysium::Core::TimeSpan & Elysium::Core::DateTimeOffset::GetOffset() const
{
	return (TimeSpan&)_Offset;
}
