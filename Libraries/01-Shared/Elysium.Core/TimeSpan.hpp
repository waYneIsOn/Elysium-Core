/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TIMESPAN
#define ELYSIUM_CORE_TIMESPAN

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core.Template/Primitives.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API TimeSpan
	{
	public:
		TimeSpan(Elysium::Core::int64_t Ticks);
		TimeSpan(Elysium::Core::int32_t Hours, Elysium::Core::int32_t Minutes, Elysium::Core::int32_t Seconds);
		TimeSpan(Elysium::Core::int32_t Hours, Elysium::Core::int32_t Minutes, Elysium::Core::int32_t Seconds, Elysium::Core::int32_t Milliseconds);
		TimeSpan(const TimeSpan& Source);
		TimeSpan(TimeSpan&& Right) noexcept;
		~TimeSpan();

		TimeSpan& operator=(const TimeSpan& Source);
		TimeSpan& operator=(TimeSpan&& Right) noexcept;

		TimeSpan operator+(const TimeSpan& Other);
		TimeSpan operator-(const TimeSpan& Other);

		TimeSpan& operator+=(const TimeSpan& Other);

		static TimeSpan Zero();

		static TimeSpan FromDays(double Value);
		static TimeSpan FromHours(double Value);
		static TimeSpan FromMinutes(double Value);
		static TimeSpan FromSeconds(double Value);
		static TimeSpan FromTicks(Elysium::Core::int64_t Value);

		const Elysium::Core::int64_t GetTicks() const;

		const Elysium::Core::int32_t GetDays() const;
		const Elysium::Core::int32_t GetHours() const;
		const Elysium::Core::int32_t GetMinutes() const;
		const Elysium::Core::int32_t GetSeconds() const;
		const Elysium::Core::int32_t GetMilliseconds() const;

		const double GetTotalDays() const;
		const double GetTotalHours() const;
		const double GetTotalMinutes() const;
		const double GetTotalSeconds() const;
		const double GetTotalMilliseconds() const;
	private:
		Elysium::Core::int64_t _Ticks;

		static TimeSpan Interval(double Value, Elysium::Core::int32_t Scale);
	};
}
#endif
