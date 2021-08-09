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
		Stopwatch();
		Stopwatch(const Stopwatch& Source) = delete;
		Stopwatch(Stopwatch&& Right) noexcept = delete;
		~Stopwatch();

		Stopwatch& operator=(const Stopwatch& Source) = delete;
		Stopwatch& operator=(Stopwatch&& Right) noexcept = delete;

		inline static Elysium::Core::int64_t Frequency = 0;	// ToDo: const
		inline static const bool IsHighResolution = QueryPerformanceFrequency((LARGE_INTEGER*)&Frequency) != 0;	// ToDo: const Frequency

		TimeSpan GetElapsed();
		const TimeSpan GetElapsed() const;
		const bool GetIsRunning() const;

		void Start();
		void Stop();
		void Reset();
	private:
		inline static const Elysium::Core::int64_t TicksPerMilliseond = 10000;
		inline static const Elysium::Core::int64_t TicksPerSecond = TicksPerMilliseond * 1000;
		inline static const double TickFrequency = 1.0;

		Elysium::Core::int64_t _Elapsed = 0;
		Elysium::Core::int64_t _StartTimeStamp = 0;
		bool _IsRunning = false;

		static Elysium::Core::int64_t GetTimestamp();
	};
}
#endif
