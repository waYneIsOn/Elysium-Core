#include "TimeSpan.hpp"

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "NotImplementedException.hpp"
#endif

#ifndef ELYSIUM_CORE_DATETIMEUTILITY
#include "DateTimeUtility.hpp"
#endif

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::TimeSpan::TimeSpan(int64_t Ticks)
	: _Ticks(Ticks)
{ }
Elysium::Core::TimeSpan::TimeSpan(int32_t Hours, int32_t Minutes, int32_t Seconds)
	: _Ticks((TimeSpan::FromHours(Hours) + TimeSpan::FromMinutes(Minutes) + TimeSpan::FromSeconds(Seconds)).GetTicks())
{ }
Elysium::Core::TimeSpan::TimeSpan(int32_t Hours, int32_t Minutes, int32_t Seconds, int32_t Milliseconds)
	: _Ticks((TimeSpan::FromHours(Hours) + TimeSpan::FromMinutes(Minutes) + TimeSpan::FromSeconds(Seconds) + TimeSpan::FromTicks(Milliseconds)).GetTicks())
{ }
Elysium::Core::TimeSpan::TimeSpan(const TimeSpan & Source)
	: _Ticks(Source._Ticks)
{ }
Elysium::Core::TimeSpan::TimeSpan(TimeSpan && Right) noexcept
	: _Ticks(0)
{
	*this = std::move(Right);
}
Elysium::Core::TimeSpan::~TimeSpan()
{ }

Elysium::Core::TimeSpan & Elysium::Core::TimeSpan::operator=(const TimeSpan & Source)
{
	if (this != &Source)
	{
		_Ticks = int64_t(Source._Ticks);
	}
	return *this;
}
Elysium::Core::TimeSpan & Elysium::Core::TimeSpan::operator=(TimeSpan && Right) noexcept
{
	if (this != &Right)
	{
		_Ticks = std::move(Right._Ticks);
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
Elysium::Core::TimeSpan Elysium::Core::TimeSpan::FromTicks(int64_t Value)
{
	return TimeSpan(Value);
}

Elysium::Core::int64_t Elysium::Core::TimeSpan::GetTicks() const
{
	return _Ticks;
}

void Elysium::Core::TimeSpan::GetDays(int * Value) const
{
	*Value = (int)(_Ticks / DateTimeUtility::TicksPerDay);
}
void Elysium::Core::TimeSpan::GetHours(int * Value) const
{
	*Value = (int)((_Ticks / DateTimeUtility::TicksPerHour) % 24);
}
void Elysium::Core::TimeSpan::GetMinutes(int * Value) const
{
	*Value = (int)((_Ticks / DateTimeUtility::TicksPerMinute) % 60);
}
void Elysium::Core::TimeSpan::GetSeconds(int * Value) const
{
	*Value = (int)((_Ticks / DateTimeUtility::TicksPerSecond) % 60);
}
void Elysium::Core::TimeSpan::GetMilliseconds(int * Value) const
{
	*Value = (int)((_Ticks / DateTimeUtility::TicksPerMillisecond) % 1000);
}

void Elysium::Core::TimeSpan::GetTotalDays(double * Value) const
{
	*Value = _Ticks * DateTimeUtility::DaysPerTick;
}
void Elysium::Core::TimeSpan::GetTotalHours(double * Value) const
{
	*Value = _Ticks * DateTimeUtility::HoursPerTick;
}
void Elysium::Core::TimeSpan::GetTotalMinutes(double * Value) const
{
	*Value = _Ticks * DateTimeUtility::MinutesPerTick;
}
void Elysium::Core::TimeSpan::GetTotalSeconds(double * Value) const
{
	*Value = _Ticks * DateTimeUtility::SecondsPerTick;
}
void Elysium::Core::TimeSpan::GetTotalMilliseconds(double * Value) const
{
	double IntermediateValue = _Ticks * DateTimeUtility::MillisecondsPerTick;
	if (IntermediateValue > DateTimeUtility::MaxMilliseconds)
	{
		*Value = DateTimeUtility::MaxMilliseconds;
	}
	else if (IntermediateValue < DateTimeUtility::MinMilliseconds)
	{
		*Value = DateTimeUtility::MinMilliseconds;
	}
	else
	{
		*Value = IntermediateValue;
	}
}

int Elysium::Core::TimeSpan::GetDays() const
{
	return (int)(_Ticks / DateTimeUtility::TicksPerDay);
}
int Elysium::Core::TimeSpan::GetHours() const
{
	return (int)((_Ticks / DateTimeUtility::TicksPerHour) % 24);
}
int Elysium::Core::TimeSpan::GetMinutes() const
{
	return (int)((_Ticks / DateTimeUtility::TicksPerMinute) % 60);
}
int Elysium::Core::TimeSpan::GetSeconds() const
{
	return (int)((_Ticks / DateTimeUtility::TicksPerSecond) % 60);
}
int Elysium::Core::TimeSpan::GetMilliseconds() const
{
	return (int)((_Ticks / DateTimeUtility::TicksPerMillisecond) % 1000);
}

double Elysium::Core::TimeSpan::GetTotalDays() const
{
	return _Ticks * DateTimeUtility::DaysPerTick;
}
double Elysium::Core::TimeSpan::GetTotalHours() const
{
	return _Ticks * DateTimeUtility::HoursPerTick;
}
double Elysium::Core::TimeSpan::GetTotalMinutes() const
{
	return _Ticks * DateTimeUtility::MinutesPerTick;
}
double Elysium::Core::TimeSpan::GetTotalSeconds() const
{
	return _Ticks * DateTimeUtility::SecondsPerTick;
}
double Elysium::Core::TimeSpan::GetTotalMilliseconds() const
{
	double IntermediateValue = (double)_Ticks * DateTimeUtility::MillisecondsPerTick;
	if (IntermediateValue > DateTimeUtility::MaxMilliseconds)
	{
		return (double)DateTimeUtility::MaxMilliseconds;
	}
	else if (IntermediateValue < DateTimeUtility::MinMilliseconds)
	{
		return (double)DateTimeUtility::MinMilliseconds;
	}
	else
	{
		return IntermediateValue;
	}
}

Elysium::Core::TimeSpan Elysium::Core::TimeSpan::Interval(double Value, int Scale)
{
	double IntermediateValue = Value * Scale;
	double Milliseconds = IntermediateValue + (Value >= 0 ? 0.5 : -0.5);

	return TimeSpan((int64_t)Milliseconds * DateTimeUtility::TicksPerMillisecond);
}
