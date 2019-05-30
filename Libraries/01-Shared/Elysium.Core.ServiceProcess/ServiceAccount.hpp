/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_SERVICEPROCESS_SERVICEACCOUNT
#define ELYSIUM_CORE_SERVICEPROCESS_SERVICEACCOUNT

namespace Elysium
{
	namespace Core
	{
		namespace ServiceProcess
		{
			enum class ServiceAccount : int
			{
				LocalService = 0,
				NetworkService = 1,
				LocalSystem = 2,
				User = 3,
			};
		}
	}
}
#endif
