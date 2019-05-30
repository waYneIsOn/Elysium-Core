#include "DateTimeUtility.hpp"

// define static DateTime fields
const int Elysium::Core::DateTimeUtility::DaysToMonth365[13] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
const int Elysium::Core::DateTimeUtility::DaysToMonth366[13] = { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 };

const double Elysium::Core::DateTimeUtility::DaysPerTick = 1.0 / TicksPerDay;
const double Elysium::Core::DateTimeUtility::HoursPerTick = 1.0 / TicksPerHour;
const double Elysium::Core::DateTimeUtility::MinutesPerTick = 1.0 / TicksPerMinute;
const double Elysium::Core::DateTimeUtility::SecondsPerTick = 1.0 / TicksPerSecond;
const double Elysium::Core::DateTimeUtility::MillisecondsPerTick = 1.0 / TicksPerMillisecond;

Elysium::Core::DateTimeUtility::DateTimeUtility()
{
}
Elysium::Core::DateTimeUtility::~DateTimeUtility()
{
}
