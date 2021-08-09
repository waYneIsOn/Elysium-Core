#include "Stopwatch.hpp"

#ifndef ELYSIUM_CORE_DATETIME
#include "../Elysium.Core/DateTime.hpp"
#endif

Elysium::Core::Diagnostics::Stopwatch::Stopwatch()
{ }
Elysium::Core::Diagnostics::Stopwatch::~Stopwatch()
{ }

Elysium::Core::TimeSpan Elysium::Core::Diagnostics::Stopwatch::GetElapsed()
{
	return TimeSpan(_Elapsed);
}

const Elysium::Core::TimeSpan Elysium::Core::Diagnostics::Stopwatch::GetElapsed() const
{
	return TimeSpan(_Elapsed);
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

Elysium::Core::int64_t Elysium::Core::Diagnostics::Stopwatch::GetTimestamp()
{
	if (IsHighResolution)
	{
		Elysium::Core::int64_t Timestamp = 0;
		QueryPerformanceCounter((LARGE_INTEGER*)&Timestamp);
		return Timestamp;
	}
	else
	{
		return DateTime::UtcNow().GetTicks();
	}
}
