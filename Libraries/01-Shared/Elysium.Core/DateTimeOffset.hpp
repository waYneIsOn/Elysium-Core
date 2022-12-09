/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATETIMEOFFSET
#define ELYSIUM_CORE_DATETIMEOFFSET

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_DATETIME
#include "DateTime.hpp"
#endif

#ifndef ELYSIUM_CORE_TIMESPAN
#include "TimeSpan.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API DateTimeOffset final
	{
	public:
		DateTimeOffset(const DateTime DateTime);

		DateTimeOffset(const DateTime DateTime, const TimeSpan Offset);

		DateTimeOffset(const DateTimeOffset& Source);

		DateTimeOffset(DateTimeOffset&& Right) noexcept;

		~DateTimeOffset();
	public:
		DateTimeOffset& operator=(const DateTimeOffset& Source);

		DateTimeOffset& operator=(DateTimeOffset&& Right) noexcept;
	public:
		DateTime& GetDateTime() const;

		TimeSpan& GetOffset() const;
	private:
		DateTime _DateTime;
		TimeSpan _Offset;
	};
}
#endif
