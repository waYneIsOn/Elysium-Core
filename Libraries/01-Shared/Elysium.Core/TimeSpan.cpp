#include "TimeSpan.hpp"

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "NotImplementedException.hpp"
#endif

#ifndef ELYSIUM_CORE_DATETIMEUTILITY
#include "DateTimeUtility.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::TimeSpan::TimeSpan(Elysium::Core::int64_t Ticks)
	: _Ticks(Ticks)
{ }
Elysium::Core::TimeSpan::TimeSpan(Elysium::Core::int32_t Hours, Elysium::Core::int32_t Minutes, Elysium::Core::int32_t Seconds)
	: _Ticks((TimeSpan::FromHours(Hours) + TimeSpan::FromMinutes(Minutes) + TimeSpan::FromSeconds(Seconds)).GetTicks())
{ }
Elysium::Core::TimeSpan::TimeSpan(Elysium::Core::int32_t Hours, Elysium::Core::int32_t Minutes, Elysium::Core::int32_t Seconds, Elysium::Core::int32_t Milliseconds)
	: _Ticks((TimeSpan::FromHours(Hours) + TimeSpan::FromMinutes(Minutes) + TimeSpan::FromSeconds(Seconds) + TimeSpan::FromTicks(Milliseconds)).GetTicks())
{ }
Elysium::Core::TimeSpan::TimeSpan(const TimeSpan & Source)
	: _Ticks(Source._Ticks)
{ }
Elysium::Core::TimeSpan::TimeSpan(TimeSpan && Right) noexcept
	: _Ticks(0)
{
	*this = Elysium::Core::Template::Functional::Move(Right);
}
Elysium::Core::TimeSpan::~TimeSpan()
{ }

Elysium::Core::TimeSpan & Elysium::Core::TimeSpan::operator=(const TimeSpan & Source)
{
	if (this != &Source)
	{
		_Ticks = Elysium::Core::int64_t(Source._Ticks);
	}
	return *this;
}
Elysium::Core::TimeSpan & Elysium::Core::TimeSpan::operator=(TimeSpan && Right) noexcept
{
	if (this != &Right)
	{
		_Ticks = Elysium::Core::Template::Functional::Move(Right._Ticks);
	}
	return *this;
}

Elysium::Core::TimeSpan Elysium::Core::TimeSpan::operator+(const TimeSpan & Other)
{
	return TimeSpan(_Ticks + Other._Ticks);
}
Elysium::Core::TimeSpan Elysium::Core::TimeSpan::operator-(const TimeSpan & Other)
{
	return TimeSpan(_Ticks - Other._Ticks);
}

Elysium::Core::TimeSpan & Elysium::Core::TimeSpan::operator+=(const TimeSpan & Other)
{
	_Ticks += Other._Ticks;
	return *this;
}

Elysium::Core::TimeSpan Elysium::Core::TimeSpan::Zero()
{
	return TimeSpan(0);
}

Elysium::Core::TimeSpan Elysium::Core::TimeSpan::FromDays(double Value)
{
	return Interval(Value, DateTimeUtility::MillisecondsPerDay);
}
Elysium::Core::TimeSpan Elysium::Core::TimeSpan::FromHours(double Value)
{
	return Interval(Value, DateTimeUtility::MillisecondsPerHour);
}
Elysium::Core::TimeSpan Elysium::Core::TimeSpan::FromMinutes(double Value)
{
	return Interval(Value, DateTimeUtility::MillisecondsPerMinute);
}
Elysium::Core::TimeSpan Elysium::Core::TimeSpan::FromSeconds(double Value)
{
	return Interval(Value, DateTimeUtility::MillisecondsPerSecond);
}
Elysium::Core::TimeSpan Elysium::Core::TimeSpan::FromTicks(Elysium::Core::int64_t Value)
{
	return TimeSpan(Value);
}

const Elysium::Core::int64_t Elysium::Core::TimeSpan::GetTicks() const
{
	return _Ticks;
}

const Elysium::Core::int32_t Elysium::Core::TimeSpan::GetDays() const
{
	return static_cast<Elysium::Core::int32_t>(_Ticks / DateTimeUtility::TicksPerDay);
}
const Elysium::Core::int32_t Elysium::Core::TimeSpan::GetHours() const
{
	return static_cast<Elysium::Core::int32_t>((_Ticks / DateTimeUtility::TicksPerHour) % 24);
}
const Elysium::Core::int32_t Elysium::Core::TimeSpan::GetMinutes() const
{
	return static_cast<Elysium::Core::int32_t>((_Ticks / DateTimeUtility::TicksPerMinute) % 60);
}
const Elysium::Core::int32_t Elysium::Core::TimeSpan::GetSeconds() const
{
	return static_cast<Elysium::Core::int32_t>((_Ticks / DateTimeUtility::TicksPerSecond) % 60);
}
const Elysium::Core::int32_t Elysium::Core::TimeSpan::GetMilliseconds() const
{
	return static_cast<Elysium::Core::int32_t>((_Ticks / DateTimeUtility::TicksPerMillisecond) % 1000);
}

const double Elysium::Core::TimeSpan::GetTotalDays() const
{
	return _Ticks * DateTimeUtility::DaysPerTick;
}
const double Elysium::Core::TimeSpan::GetTotalHours() const
{
	return _Ticks * DateTimeUtility::HoursPerTick;
}
const double Elysium::Core::TimeSpan::GetTotalMinutes() const
{
	return _Ticks * DateTimeUtility::MinutesPerTick;
}
const double Elysium::Core::TimeSpan::GetTotalSeconds() const
{
	return _Ticks * DateTimeUtility::SecondsPerTick;
}
const double Elysium::Core::TimeSpan::GetTotalMilliseconds() const
{
	double IntermediateValue = static_cast<double>(_Ticks * DateTimeUtility::MillisecondsPerTick);
	if (IntermediateValue > DateTimeUtility::MaxMilliseconds)
	{
		return static_cast<double>(DateTimeUtility::MaxMilliseconds);
	}
	else if (IntermediateValue < DateTimeUtility::MinMilliseconds)
	{
		return static_cast<double>(DateTimeUtility::MinMilliseconds);
	}
	else
	{
		return IntermediateValue;
	}
}

Elysium::Core::TimeSpan Elysium::Core::TimeSpan::Interval(double Value, Elysium::Core::int32_t Scale)
{
	double IntermediateValue = Value * Scale;
	double Milliseconds = IntermediateValue + (Value >= 0 ? 0.5 : -0.5);

	return TimeSpan(static_cast<Elysium::Core::int64_t>(Milliseconds) * DateTimeUtility::TicksPerMillisecond);
}
