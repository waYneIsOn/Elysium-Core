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
		enum class DateTimeKind : long
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