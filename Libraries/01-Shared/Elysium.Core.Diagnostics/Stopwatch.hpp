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
#include "../Elysium.Core.Template/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TIMESPAN
#include "../Elysium.Core/TimeSpan.hpp"
#endif

namespace Elysium::Core::Diagnostics
{
	class ELYSIUM_CORE_API Stopwatch final
	{
	private:
		static const bool SetupGetIsHighResolution();
		static const Elysium::Core::int64_t SetupGetFrequency();
		static const double SetupGetTickFrequency();
	public:
		Stopwatch();
		Stopwatch(const Stopwatch& Source) = delete;
		Stopwatch(Stopwatch&& Right) noexcept = delete;
		~Stopwatch();

		Stopwatch& operator=(const Stopwatch& Source) = delete;
		Stopwatch& operator=(Stopwatch&& Right) noexcept = delete;

		inline static const bool IsHighResolution = SetupGetIsHighResolution();
		inline static const Elysium::Core::int64_t Frequency = SetupGetFrequency();

		TimeSpan GetElapsed() const;
		const bool GetIsRunning() const;

		void Start();
		void Stop();
		void Reset();
	private:
		inline static const Elysium::Core::int64_t TicksPerMilliseond = 10000;
		inline static const Elysium::Core::int64_t TicksPerSecond = TicksPerMilliseond * 1000;
		inline static const double TickFrequency = SetupGetTickFrequency();

		Elysium::Core::int64_t _Elapsed = 0;
		Elysium::Core::int64_t _StartTimeStamp = 0;
		bool _IsRunning = false;

		static const Elysium::Core::int64_t GetTimestamp();

		const Elysium::Core::int64_t GetRawElapsedTicks() const;
		const Elysium::Core::int64_t GetElapsedDateTimeTicks() const;
	};
}
#endif
