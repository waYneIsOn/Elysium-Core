#include "Stopwatch.hpp"

#ifndef ELYSIUM_CORE_DATETIME
#include "../Elysium.Core/DateTime.hpp"
#endif

const bool Elysium::Core::Diagnostics::Stopwatch::SetupGetIsHighResolution()
{
	LARGE_INTEGER Timestamp;
	return QueryPerformanceFrequency(&Timestamp) != 0;
}

const Elysium::Core::int64_t Elysium::Core::Diagnostics::Stopwatch::SetupGetFrequency()
{
	LARGE_INTEGER Timestamp;
	if (QueryPerformanceFrequency(&Timestamp) == 0)
	{
		return TicksPerSecond;
	}
	else
	{
		return Timestamp.QuadPart;
	}
}

const double Elysium::Core::Diagnostics::Stopwatch::SetupGetTickFrequency()
{
	LARGE_INTEGER Timestamp;
	if (QueryPerformanceFrequency(&Timestamp) == 0)
	{
		return 1.0f;
	}
	else
	{
		return TicksPerSecond / Timestamp.QuadPart;
	}
}

Elysium::Core::Diagnostics::Stopwatch::Stopwatch()
{ }
Elysium::Core::Diagnostics::Stopwatch::~Stopwatch()
{ }

Elysium::Core::TimeSpan Elysium::Core::Diagnostics::Stopwatch::GetElapsed() const
{
	return TimeSpan(GetElapsedDateTimeTicks());
}

const bool Elysium::Core::Diagnostics::Stopwatch::GetIsRunning() const
{
	return _IsRunning;
}

void Elysium::Core::Diagnostics::Stopwatch::Start()
{
	if (!_IsRunning)
	{
		_StartTimeStamp = GetTimestamp();
		_IsRunning = true;
	}
}

void Elysium::Core::Diagnostics::Stopwatch::Stop()
{
	if (_IsRunning)
	{
		Elysium::Core::int64_t EndTimeStamp = GetTimestamp();
		Elysium::Core::int64_t ElapsedThisPeriod = EndTimeStamp - _StartTimeStamp;
		_Elapsed += ElapsedThisPeriod;
		_IsRunning = false;

		if (_Elapsed < 0)
		{
			_Elapsed = 0;
		}
	}
}

void Elysium::Core::Diagnostics::Stopwatch::Reset()
{
	_Elapsed = 0;
	_StartTimeStamp = 0;
	_IsRunning = false;
}

const Elysium::Core::int64_t Elysium::Core::Diagnostics::Stopwatch::GetTimestamp()
{
	if (IsHighResolution)
	{
		LARGE_INTEGER Timestamp;
		QueryPerformanceCounter(&Timestamp);
		return Timestamp.QuadPart;
	}
	else
	{
		return DateTime::UtcNow().GetTicks();
	}
}

const Elysium::Core::int64_t Elysium::Core::Diagnostics::Stopwatch::GetRawElapsedTicks() const
{
	Elysium::Core::int64_t TimeElapsed = _Elapsed;
	if (_IsRunning)
	{
		const Elysium::Core::int64_t CurrentTimeStamp = GetTimestamp();
		const Elysium::Core::int64_t ElapsedUntilNow = CurrentTimeStamp - _StartTimeStamp;
		TimeElapsed += ElapsedUntilNow;
	}
	return TimeElapsed;
}

const Elysium::Core::int64_t Elysium::Core::Diagnostics::Stopwatch::GetElapsedDateTimeTicks() const
{
	const Elysium::Core::int64_t RawTicks = GetRawElapsedTicks();
	if (IsHighResolution)
	{
		double RawTicksAsDouble = RawTicks;
		RawTicksAsDouble *= TickFrequency;
		return static_cast<Elysium::Core::int64_t>(RawTicksAsDouble);
	}
	else
	{
		return RawTicks;
	}
}
