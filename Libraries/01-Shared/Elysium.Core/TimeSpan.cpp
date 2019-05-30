#include "TimeSpan.hpp"

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "NotImplementedException.hpp"
#endif

#ifndef ELYSIUM_CORE_DATETIMEUTILITY
#include "DateTimeUtility.hpp"
#endif

Elysium::Core::TimeSpan::TimeSpan(__int64 Ticks)
	: _Ticks(Ticks)
{
}
Elysium::Core::TimeSpan::TimeSpan(__int32 Hours, __int32 Minutes, __int32 Seconds)
	: Elysium::Core::TimeSpan::TimeSpan(TimeSpan::FromHours(Hours) + TimeSpan::FromMinutes(Minutes) + TimeSpan::FromSeconds(Seconds))
{
}
Elysium::Core::TimeSpan::TimeSpan(__int32 Hours, __int32 Minutes, __int32 Seconds, __int32 Milliseconds)
	: Elysium::Core::TimeSpan::TimeSpan(TimeSpan::FromHours(Hours) + TimeSpan::FromMinutes(Minutes) + TimeSpan::FromSeconds(Seconds) + TimeSpan::FromTicks(Milliseconds))
{
}
Elysium::Core::TimeSpan::TimeSpan(const TimeSpan & Source)
	: _Ticks(Source._Ticks)
{
}
Elysium::Core::TimeSpan::~TimeSpan()
{
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
Elysium::Core::TimeSpan Elysium::Core::TimeSpan::FromTicks(__int64 Value)
{
	return TimeSpan(Value);
}

__int64 Elysium::Core::TimeSpan::GetTicks() const
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
	*Value = (double)_Ticks * DateTimeUtility::DaysPerTick;
}
void Elysium::Core::TimeSpan::GetTotalHours(double * Value) const
{
	*Value = (double)_Ticks * DateTimeUtility::HoursPerTick;
}
void Elysium::Core::TimeSpan::GetTotalMinutes(double * Value) const
{
	*Value = (double)_Ticks * DateTimeUtility::MinutesPerTick;
}
void Elysium::Core::TimeSpan::GetTotalSeconds(double * Value) const
{
	*Value = (double)_Ticks * DateTimeUtility::SecondsPerTick;
}
void Elysium::Core::TimeSpan::GetTotalMilliseconds(double * Value) const
{
	double IntermediateValue = (double)_Ticks * DateTimeUtility::MillisecondsPerTick;
	if (IntermediateValue > DateTimeUtility::MaxMilliseconds)
	{
		*Value = (double)DateTimeUtility::MaxMilliseconds;
	}
	else if (IntermediateValue < DateTimeUtility::MinMilliseconds)
	{
		*Value = (double)DateTimeUtility::MinMilliseconds;
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
	return (double)_Ticks * DateTimeUtility::DaysPerTick;
}
double Elysium::Core::TimeSpan::GetTotalHours() const
{
	return (double)_Ticks * DateTimeUtility::HoursPerTick;
}
double Elysium::Core::TimeSpan::GetTotalMinutes() const
{
	return (double)_Ticks * DateTimeUtility::MinutesPerTick;
}
double Elysium::Core::TimeSpan::GetTotalSeconds() const
{
	return (double)_Ticks * DateTimeUtility::SecondsPerTick;
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

Elysium::Core::TimeSpan Elysium::Core::TimeSpan::Interval(double Value, int Scale)
{
	double IntermediateValue = Value * Scale;
	double Milliseconds = IntermediateValue + (Value >= 0 ? 0.5 : -0.5);

	return TimeSpan((__int64)Milliseconds * DateTimeUtility::TicksPerMillisecond);
}
