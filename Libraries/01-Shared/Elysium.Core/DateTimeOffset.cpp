#include "DateTimeOffset.hpp"

Elysium::Core::DateTimeOffset::DateTimeOffset(const DateTime DateTime)
	: Elysium::Core::DateTimeOffset::DateTimeOffset(DateTime, TimeSpan::Zero())
{
}
Elysium::Core::DateTimeOffset::DateTimeOffset(const DateTime DateTime, const TimeSpan Offset)
	: _DateTime(DateTime), _Offset(Offset)
{
}
Elysium::Core::DateTimeOffset::~DateTimeOffset()
{
}

Elysium::Core::DateTime & Elysium::Core::DateTimeOffset::GetDateTime() const
{
	return (DateTime&)_DateTime;
}

Elysium::Core::TimeSpan & Elysium::Core::DateTimeOffset::GetOffset() const
{
	return (TimeSpan&)_Offset;
}
