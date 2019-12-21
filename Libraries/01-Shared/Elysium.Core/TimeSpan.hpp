/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_TIMESPAN
#define ELYSIUM_CORE_TIMESPAN

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef _STDINT_H
#include <cstdint>
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API TimeSpan
	{
	public:
		TimeSpan(int64_t Ticks);
		TimeSpan(int32_t Hours, int32_t Minutes, int32_t Seconds);
		TimeSpan(int32_t Hours, int32_t Minutes, int32_t Seconds, int32_t Milliseconds);
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
		static TimeSpan FromTicks(int64_t Value);

		int64_t GetTicks() const;

		void GetDays(int* Value) const;
		void GetHours(int* Value) const;
		void GetMinutes(int* Value) const;
		void GetSeconds(int* Value) const;
		void GetMilliseconds(int* Value) const;

		void GetTotalDays(double* Value) const;
		void GetTotalHours(double* Value) const;
		void GetTotalMinutes(double* Value) const;
		void GetTotalSeconds(double* Value) const;
		void GetTotalMilliseconds(double* Value) const;

		int GetDays() const;
		int GetHours() const;
		int GetMinutes() const;
		int GetSeconds() const;
		int GetMilliseconds() const;

		double GetTotalDays() const;
		double GetTotalHours() const;
		double GetTotalMinutes() const;
		double GetTotalSeconds() const;
		double GetTotalMilliseconds() const;
	private:
		int64_t _Ticks;

		static TimeSpan Interval(double Value, int Scale);
	};
}
#endif
