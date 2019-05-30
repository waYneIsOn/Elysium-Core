/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_TIMESPAN
#define ELYSIUM_CORE_TIMESPAN

#ifndef ELYSIUM_CORE_EXPORT
#include "Export.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		class EXPORT TimeSpan
		{
		public:
			TimeSpan(__int64 Ticks);
			TimeSpan(__int32 Hours, __int32 Minutes, __int32 Seconds);
			TimeSpan(__int32 Hours, __int32 Minutes, __int32 Seconds, __int32 Milliseconds);
			TimeSpan(const TimeSpan& Source);
			~TimeSpan();

			static TimeSpan Zero();

			static TimeSpan FromDays(double Value);
			static TimeSpan FromHours(double Value);
			static TimeSpan FromMinutes(double Value);
			static TimeSpan FromSeconds(double Value);
			static TimeSpan FromTicks(__int64 Value);

			__int64 GetTicks() const;

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

			TimeSpan operator+(const TimeSpan& Other);
			TimeSpan operator-(const TimeSpan& Other);

			TimeSpan& operator+=(const TimeSpan& Other);
		private:
			__int64 _Ticks;

			static TimeSpan Interval(double Value, int Scale);
		};
	}
}
#endif
