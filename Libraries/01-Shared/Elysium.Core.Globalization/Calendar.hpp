/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_GLOBALIZATION_CALENDAR
#define ELYSIUM_CORE_GLOBALIZATION_CALENDAR

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

#ifndef ELYSIUM_CORE_GLOBALIZATION_CALENDARALGORITHMTYPE
#include "CalendarAlgorithmType.hpp"
#endif

namespace Elysium::Core::Globalization
{
	class ELYSIUM_CORE_API Calendar
	{
	public:
		Calendar(const Calendar& Source) = delete;
		Calendar(Calendar&& Right) noexcept = delete;
		virtual ~Calendar();

		Calendar& operator=(const Calendar& Source) = delete;
		Calendar& operator=(Calendar&& Right) noexcept = delete;

		static void Test();
	protected:
		Calendar();
	private:
		Elysium::Core::String _Name;
		//Elysium::Core::int32_t _LCID;
	};
}
#endif
