/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DIAGNOSTICS_STOPWATCH
#define ELYSIUM_CORE_DIAGNOSTICS_STOPWATCH

#ifdef _MSC_VER
#pragma once
#endif

#ifndef _WINDOWS_
#include <windows.h>
#endif

#ifndef _PROFILEAPI_H_
#include <profileapi.h>
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TIMESPAN
#include "../Elysium.Core/TimeSpan.hpp"
#endif

namespace Elysium::Core::Diagnostics
{
	class ELYSIUM_CORE_API Stopwatch final
	{
	public:
		constexpr Stopwatch() = default;

		constexpr Stopwatch(const Stopwatch& Source) = delete;

		constexpr Stopwatch(Stopwatch&& Right) noexcept = delete;

		constexpr ~Stopwatch() = default;
	public:
		constexpr Stopwatch& operator=(const Stopwatch& Source) = delete;

		constexpr Stopwatch& operator=(Stopwatch&& Right) noexcept = delete;
	public:
		TimeSpan GetElapsed() const;

		const bool GetIsRunning() const;

		void Start();

		void Stop();

		void Reset();
	private:
		static const bool SetupIsHighResolution();

		static const Elysium::Core::int64_t SetupGetFrequency();

		static const double SetupTickFrequency();
	public:
		inline static const bool IsHighResolution = SetupIsHighResolution();

		inline static const Elysium::Core::int64_t Frequency = SetupGetFrequency();
	private:
		inline static constexpr const Elysium::Core::int64_t _TicksPerMilliseond = 10000;
		inline static constexpr const Elysium::Core::int64_t _TicksPerSecond = _TicksPerMilliseond * 1000;
		inline static const double _TickFrequency = SetupTickFrequency();
	private:
		Elysium::Core::int64_t _Elapsed = 0;
		Elysium::Core::int64_t _StartTimeStamp = 0;
		bool _IsRunning = false;
	private:
		static const Elysium::Core::int64_t GetTimestamp();
	private:
		constexpr const Elysium::Core::int64_t GetRawElapsedTicks() const;

		constexpr const Elysium::Core::int64_t GetElapsedDateTimeTicks() const;
	};

	inline const bool Elysium::Core::Diagnostics::Stopwatch::SetupIsHighResolution()
	{
		LARGE_INTEGER Timestamp;
		return QueryPerformanceFrequency(&Timestamp) != 0;
	}

	inline const Elysium::Core::int64_t Elysium::Core::Diagnostics::Stopwatch::SetupGetFrequency()
	{
		LARGE_INTEGER Timestamp;
		if (QueryPerformanceFrequency(&Timestamp) == 0)
		{
			return _TicksPerSecond;
		}
		else
		{
			return Timestamp.QuadPart;
		}
	}

	inline const double Elysium::Core::Diagnostics::Stopwatch::SetupTickFrequency()
	{
		LARGE_INTEGER Timestamp;
		if (QueryPerformanceFrequency(&Timestamp) == 0)
		{
			return 1.0f;
		}
		else
		{
			return static_cast<double>(_TicksPerSecond / Timestamp.QuadPart);
		}
	}
}
#endif
