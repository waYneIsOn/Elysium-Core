#include "DateTime.hpp"

#ifndef ELYSIUM_CORE_ARGUMENTOUTOFRANGEEXCEPTION
#include "ArgumentOutOfRangeException.hpp"
#endif

#ifndef ELYSIUM_CORE_DATETIMEUTILITY
#include "DateTimeUtility.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "NotImplementedException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS
#include "../Elysium.Core.Template/TypeTraits.hpp"
#endif

#ifndef _CHRONO_
#include <chrono>
#endif

Elysium::Core::DateTime::DateTime(Elysium::Core::int64_t Ticks)
	: Elysium::Core::DateTime::DateTime(Ticks, DateTimeKind::Unspecified)
{ }
Elysium::Core::DateTime::DateTime(Elysium::Core::int64_t Ticks, DateTimeKind Kind)
	: _Ticks(Ticks), _Kind(Kind)
{ }
Elysium::Core::DateTime::DateTime(Elysium::Core::int32_t Year, Elysium::Core::int32_t Month, Elysium::Core::int32_t Day)
	: Elysium::Core::DateTime::DateTime(DateToTicks(Year, Month, Day))
{ }
Elysium::Core::DateTime::DateTime(Elysium::Core::int32_t Year, Elysium::Core::int32_t Month, Elysium::Core::int32_t Day, Elysium::Core::int32_t Hour, Elysium::Core::int32_t Minute, Elysium::Core::int32_t Second)
	: Elysium::Core::DateTime::DateTime(DateToTicks(Year, Month, Day) + TimeToTicks(Hour, Minute, Second))
{ }
Elysium::Core::DateTime::DateTime(Elysium::Core::int32_t Year, Elysium::Core::int32_t Month, Elysium::Core::int32_t Day, Elysium::Core::int32_t Hour, Elysium::Core::int32_t Minute, Elysium::Core::int32_t Second, Elysium::Core::int32_t Millisecond)
	: Elysium::Core::DateTime::DateTime(DateToTicks(Year, Month, Day) + TimeToTicks(Hour, Minute, Second) + Millisecond * DateTimeUtility::TicksPerMillisecond)
{ }
Elysium::Core::DateTime::DateTime(const DateTime & Source)
	: _Ticks(Source._Ticks), _Kind(Source._Kind)
{ }
Elysium::Core::DateTime::DateTime(DateTime && Right) noexcept
	: Elysium::Core::DateTime::DateTime(0, DateTimeKind::Unspecified)
{
	*this = Elysium::Core::Template::TypeTraits::Move(Right);
}
Elysium::Core::DateTime::~DateTime()
{ }

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
		_Ticks = Elysium::Core::Template::TypeTraits::Move(Right._Ticks);
		_Kind = Elysium::Core::Template::TypeTraits::Move(Right._Kind);

		Right._Ticks = 0;
		Right._Kind = DateTimeKind::Unspecified;
	}
	return *this;
}

Elysium::Core::TimeSpan Elysium::Core::DateTime::operator+(const DateTime & Other) noexcept
{
	return TimeSpan(_Ticks + Other._Ticks);
}
Elysium::Core::TimeSpan Elysium::Core::DateTime::operator-(const DateTime & Other) noexcept
{
	return TimeSpan(_Ticks - Other._Ticks);
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
	//return DateTime(std::chrono::high_resolution_clock::now().time_since_epoch().count() / 100, DateTimeKind::Local);
	return DateTime(std::chrono::system_clock::now().time_since_epoch().count(), DateTimeKind::Local);
}
Elysium::Core::DateTime Elysium::Core::DateTime::Today()
{
	throw NotImplementedException(u8"Elysium::Core::DateTime Elysium::Core::DateTime::Today");
}
Elysium::Core::DateTime Elysium::Core::DateTime::UtcNow()
{
	return DateTime(std::chrono::utc_clock::now().time_since_epoch().count(), DateTimeKind::Utc);
}

const Elysium::Core::DateTimeKind Elysium::Core::DateTime::GetKind() const
{
	return _Kind;
}
const Elysium::Core::int64_t Elysium::Core::DateTime::GetTicks() const
{
	return _Ticks;
}

const Elysium::Core::int32_t Elysium::Core::DateTime::GetDay() const
{
	return GetDatePart(DatePart::Day);
}
const Elysium::Core::int32_t Elysium::Core::DateTime::GetHour() const
{
	return ((_Ticks / DateTimeUtility::TicksPerHour) % 24);
}
const Elysium::Core::int32_t Elysium::Core::DateTime::GetMillisecond() const
{
	return ((_Ticks / DateTimeUtility::TicksPerMillisecond) % 1000);
}
const Elysium::Core::int32_t Elysium::Core::DateTime::GetMinute() const
{
	return ((_Ticks / DateTimeUtility::TicksPerMinute) % 60);
}
const Elysium::Core::int32_t Elysium::Core::DateTime::GetMonth() const
{
	return GetDatePart(DatePart::Month);
}
const Elysium::Core::int32_t Elysium::Core::DateTime::GetSecond() const
{
	return ((_Ticks / DateTimeUtility::TicksPerSecond) % 60);
}
const Elysium::Core::int32_t Elysium::Core::DateTime::GetYear() const
{
	return GetDatePart(DatePart::Year);
}

const bool Elysium::Core::DateTime::IsLeapYear(const Elysium::Core::int32_t Year)
{
	if (Year >= 1 && Year <= 9999)
	{
		return Year % 4 == 0 && (Year % 100 != 0 || Year % 400 == 0);
	}
	else
	{
		throw ArgumentOutOfRangeException();
	}
}

int64_t Elysium::Core::DateTime::DateToTicks(const Elysium::Core::int32_t Year, const Elysium::Core::int32_t Month, const Elysium::Core::int32_t Day)
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
	throw ArgumentOutOfRangeException();
}
int64_t Elysium::Core::DateTime::TimeToTicks(const Elysium::Core::int32_t Hour, const Elysium::Core::int32_t Minute, const Elysium::Core::int32_t Second)
{
	if (Hour >= 0 && Hour <= 24 && Minute >= 0 && Minute < 60 && Second >= 0 && Second < 60)
	{
		int64_t TotalSeconds = (int64_t)Hour * 3600 + (int64_t)Minute * 60 + (int64_t)Second;
		if (TotalSeconds > DateTimeUtility::MaxSeconds || TotalSeconds < DateTimeUtility::MinSeconds)
		{
			throw ArgumentOutOfRangeException();
		}
		return TotalSeconds * DateTimeUtility::TicksPerSecond;
	}
	throw ArgumentOutOfRangeException();
}

const Elysium::Core::int32_t Elysium::Core::DateTime::GetDatePart(const Elysium::Core::DatePart Part) const
{
	Elysium::Core::int32_t DaysSince_01_01_0001 = static_cast<Elysium::Core::int32_t>(_Ticks / DateTimeUtility::TicksPerDay);
	Elysium::Core::int32_t Year400 = DaysSince_01_01_0001 / DateTimeUtility::DaysPer400Years;
	DaysSince_01_01_0001 -= Year400 * DateTimeUtility::DaysPer400Years;
	Elysium::Core::int32_t Year100 = Year400 / DateTimeUtility::DaysPer100Years;
	if (Year100 == 4)
	{
		Year100 = 3;
	}
	DaysSince_01_01_0001 -= Year100 * DateTimeUtility::DaysPer100Years;
	Elysium::Core::int32_t Year4 = DaysSince_01_01_0001 / DateTimeUtility::DaysPer4Years;
	DaysSince_01_01_0001 -= Year4 * DateTimeUtility::DaysPer4Years;
	Elysium::Core::int32_t Year1 = DaysSince_01_01_0001 / DateTimeUtility::DaysPerYear;
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

	const bool IsLeapYear = Year1 == 3 && (Year4 != 24 || Year100 == 3);
	const Elysium::Core::int32_t* Days = IsLeapYear ? DateTimeUtility::DaysToMonth366 : DateTimeUtility::DaysToMonth365;
	Elysium::Core::int32_t Month = (DaysSince_01_01_0001 >> 5) + 1;
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
