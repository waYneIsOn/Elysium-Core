#include "DateTime.hpp"

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "NotImplementedException.hpp"
#endif

#ifndef ELYSIUM_CORE_DATETIMEUTILITY
#include "DateTimeUtility.hpp"
#endif

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

#ifndef _CHRONO_
#include <chrono>
#endif

Elysium::Core::DateTime::DateTime(int64_t Ticks)
	: Elysium::Core::DateTime::DateTime(Ticks, DateTimeKind::Unspecified)
{
}
Elysium::Core::DateTime::DateTime(int64_t Ticks, DateTimeKind Kind)
	: _Ticks(Ticks), _Kind(Kind)
{
}
Elysium::Core::DateTime::DateTime(int Year, int Month, int Day)
	: Elysium::Core::DateTime::DateTime(DateToTicks(Year, Month, Day))
{
}
Elysium::Core::DateTime::DateTime(int Year, int Month, int Day, int Hour, int Minute, int Second)
	: Elysium::Core::DateTime::DateTime(DateToTicks(Year, Month, Day) + TimeToTicks(Hour, Minute, Second))
{
}
Elysium::Core::DateTime::DateTime(int Year, int Month, int Day, int Hour, int Minute, int Second, int Millisecond)
	: Elysium::Core::DateTime::DateTime(DateToTicks(Year, Month, Day) + TimeToTicks(Hour, Minute, Second) + Millisecond * DateTimeUtility::TicksPerMillisecond)
{
}
Elysium::Core::DateTime::DateTime(const DateTime & Source)
	: _Ticks(Source._Ticks), _Kind(Source._Kind)
{
}
Elysium::Core::DateTime::DateTime(DateTime && Right) noexcept
	: Elysium::Core::DateTime::DateTime(0, DateTimeKind::Unspecified)
{
	*this = std::move(Right);
}
Elysium::Core::DateTime::~DateTime()
{
}

Elysium::Core::DateTime & Elysium::Core::DateTime::operator=(const DateTime & Source)
{
	if (this != &Source)
	{
		_Ticks = int64_t(Source._Ticks);
		_Kind = DateTimeKind(Source._Kind);
	}
	return *this;
}
Elysium::Core::DateTime & Elysium::Core::DateTime::operator=(DateTime && Right) noexcept
{
	if (this != &Right)
	{
		_Ticks = std::move(Right._Ticks);
		_Kind = std::move(Right._Kind);

		Right._Ticks = 0;
		Right._Kind = DateTimeKind::Unspecified;
	}
	return *this;
}

Elysium::Core::DateTime Elysium::Core::DateTime::MaxValue()
{
	return DateTime(DateTimeUtility::MaxTicks, DateTimeKind::Unspecified);
}
Elysium::Core::DateTime Elysium::Core::DateTime::MinValue()
{
	return DateTime(DateTimeUtility::MinTicks, DateTimeKind::Unspecified);
}
Elysium::Core::DateTime Elysium::Core::DateTime::Now()
{
	// ToDo: UtcNow.ToLocalTime()
	return DateTime(std::chrono::high_resolution_clock::now().time_since_epoch().count(), DateTimeKind::Local);
}
Elysium::Core::DateTime Elysium::Core::DateTime::Today()
{
	throw NotImplementedException(u"Elysium::Core::DateTime Elysium::Core::DateTime::Today");
}
Elysium::Core::DateTime Elysium::Core::DateTime::UtcNow()
{
	//return DateTime(std::chrono::utc_clock::now().time_since_epoch().count(), DateTimeKind::Utc);
	throw NotImplementedException(u"Elysium::Core::DateTime Elysium::Core::DateTime::UtcNow");
}

Elysium::Core::DateTimeKind const Elysium::Core::DateTime::GetKind() const
{
	return _Kind;
}
int64_t const Elysium::Core::DateTime::GetTicks() const
{
	return _Ticks;
}

void Elysium::Core::DateTime::GetDay(int * Value) const
{
	*Value = GetDatePart(DatePart::Day);
}
void Elysium::Core::DateTime::GetHour(int * Value) const
{
	*Value = (int)((_Ticks / DateTimeUtility::TicksPerHour) % 24);
}
void Elysium::Core::DateTime::GetMillisecond(int * Value) const
{
	*Value = (int)((_Ticks / DateTimeUtility::TicksPerMillisecond) % 1000);
}
void Elysium::Core::DateTime::GetMinute(int * Value) const
{
	*Value = (int)((_Ticks / DateTimeUtility::TicksPerMinute) % 60);
}
void Elysium::Core::DateTime::GetMonth(int * Value) const
{
	*Value = GetDatePart(DatePart::Month);
}
void Elysium::Core::DateTime::GetSecond(int * Value) const
{
	*Value = (int)((_Ticks / DateTimeUtility::TicksPerSecond) % 60);
}
void Elysium::Core::DateTime::GetYear(int * Value) const
{

	*Value = GetDatePart(DatePart::Year);
}

const int Elysium::Core::DateTime::GetDay() const
{
	int Value;
	GetDay(&Value);
	return Value;
}
const int Elysium::Core::DateTime::GetHour() const
{
	int Value;
	GetHour(&Value);
	return Value;
}
const int Elysium::Core::DateTime::GetMillisecond() const
{
	int Value;
	GetMillisecond(&Value);
	return Value;
}
const int Elysium::Core::DateTime::GetMinute() const
{
	int Value;
	GetMinute(&Value);
	return Value;
}
const int Elysium::Core::DateTime::GetMonth() const
{
	int Value;
	GetMonth(&Value);
	return Value;
}
const int Elysium::Core::DateTime::GetSecond() const
{
	int Value;
	GetSecond(&Value);
	return Value;
}
const int Elysium::Core::DateTime::GetYear() const
{
	int Value;
	GetYear(&Value);
	return Value;
}

bool Elysium::Core::DateTime::IsLeapYear(int Year)
{
	if (Year >= 1 && Year <= 9999)
	{
		return Year % 4 == 0 && (Year % 100 != 0 || Year % 400 == 0);
	}
	else
	{	// ToDo: ArgumentOutOfRangeException
		throw new Exception(u"argument out of range");
	}
}

int64_t Elysium::Core::DateTime::DateToTicks(int Year, int Month, int Day)
{
	if (Year >= 1 && Year <= 9999 && Month >= 1 && Month <= 12)
	{
		const int* Days = IsLeapYear(Year) ? DateTimeUtility::DaysToMonth366 : DateTimeUtility::DaysToMonth365;
		if (Day >= 1 && Day <= Days[Month] - Days[Month - 1])
		{
			int LastYear = Year - 1;
			int DayTicks = LastYear * 365 + LastYear / 4 - LastYear / 100 + LastYear / 400 + Days[Month - 1] + Day - 1;
			return DayTicks * DateTimeUtility::TicksPerDay;
		}
	}
	// ToDo: ArgumentOutOfRangeException
	throw new Exception(u"argument out of range");
}
int64_t Elysium::Core::DateTime::TimeToTicks(int Hour, int Minute, int Second)
{
	if (Hour >= 0 && Hour <= 24 && Minute >= 0 && Minute < 60 && Second >= 0 && Second < 60)
	{
		int64_t TotalSeconds = (int64_t)Hour * 3600 + (int64_t)Minute * 60 + (int64_t)Second;
		if (TotalSeconds > DateTimeUtility::MaxSeconds || TotalSeconds < DateTimeUtility::MinSeconds)
		{
			// ToDo: ArgumentOutOfRangeException
			throw new Exception(u"argument out of range");
		}
		return TotalSeconds * DateTimeUtility::TicksPerSecond;
	}
	// ToDo: ArgumentOutOfRangeException
	throw new Exception(u"argument out of range");
}

int Elysium::Core::DateTime::GetDatePart(DatePart Part) const
{
	int DaysSince_01_01_0001 = (int)(_Ticks / DateTimeUtility::TicksPerDay);
	int Year400 = DaysSince_01_01_0001 / DateTimeUtility::DaysPer400Years;
	DaysSince_01_01_0001 -= Year400 * DateTimeUtility::DaysPer400Years;
	int Year100 = Year400 / DateTimeUtility::DaysPer100Years;
	if (Year100 == 4)
	{
		Year100 = 3;
	}
	DaysSince_01_01_0001 -= Year100 * DateTimeUtility::DaysPer100Years;
	int Year4 = DaysSince_01_01_0001 / DateTimeUtility::DaysPer4Years;
	DaysSince_01_01_0001 -= Year4 * DateTimeUtility::DaysPer4Years;
	int Year1 = DaysSince_01_01_0001 / DateTimeUtility::DaysPerYear;
	if (Year1 == 4)
	{
		Year1 = 3;
	}
	if (Part == DatePart::Year)
	{
		return Year400 * 400 + Year100 * 100 + Year4 * 4 + Year1 + 1;
	}

	DaysSince_01_01_0001 -= Year1 * DateTimeUtility::DaysPerYear;
	if (Part == DatePart::DayOfYear)
	{
		return DaysSince_01_01_0001 + 1;
	}

	bool IsLeapYear = Year1 == 3 && (Year4 != 24 || Year100 == 3);
	const int* Days = IsLeapYear ? DateTimeUtility::DaysToMonth366 : DateTimeUtility::DaysToMonth365;
	int Month = (DaysSince_01_01_0001 >> 5) + 1;
	while (DaysSince_01_01_0001 >= Days[Month])
	{
		Month++;
	}
	if (Part == DatePart::Month)
	{
		return Month;
	}

	return DaysSince_01_01_0001 - Days[Month - 1] + 1;
}
