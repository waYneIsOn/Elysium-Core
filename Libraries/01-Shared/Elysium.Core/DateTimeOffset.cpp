#include "DateTimeOffset.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::DateTimeOffset::DateTimeOffset(const DateTime DateTime)
	: Elysium::Core::DateTimeOffset::DateTimeOffset(DateTime, TimeSpan::Zero())
{
}
Elysium::Core::DateTimeOffset::DateTimeOffset(const DateTime DateTime, const TimeSpan Offset)
	: _DateTime(DateTime), _Offset(Offset)
{
}
Elysium::Core::DateTimeOffset::DateTimeOffset(const DateTimeOffset & Source)
	: _DateTime(DateTime(Source._DateTime)), _Offset(TimeSpan(Source._Offset))
{
}
Elysium::Core::DateTimeOffset::DateTimeOffset(DateTimeOffset && Right)
	: _DateTime(0), _Offset(0)
{
	*this = std::move(Right);
}
Elysium::Core::DateTimeOffset::~DateTimeOffset()
{
}

Elysium::Core::DateTimeOffset & Elysium::Core::DateTimeOffset::operator=(const DateTimeOffset & Source)
{
	if (this != &Source)
	{
		_DateTime = DateTime(Source._DateTime);
		_Offset = TimeSpan(Source._Offset);
	}
	return *this;
}
Elysium::Core::DateTimeOffset & Elysium::Core::DateTimeOffset::operator=(DateTimeOffset && Right)
{
	if (this != &Right)
	{
		_DateTime = std::move(Right._DateTime);
		_Offset = std::move(Right._Offset);
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
