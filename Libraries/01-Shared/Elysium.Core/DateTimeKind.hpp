/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_DATETIMEKIND
#define ELYSIUM_CORE_DATETIMEKIND

namespace Elysium
{
	namespace Core
	{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
		enum class DateTimeKind : long
#elif defined(__ANDROID__)
		enum class DateTimeKind
#else
#error "undefined os"
#endif
		{
			// ...
			Unspecified = 0,

			// ...
			Utc = 1,

			// ...
			Local = 2
		};
	}
}
#endif