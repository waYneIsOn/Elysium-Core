/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_SERVICEPROCESS_SERVICECONTROLLERPERMISSIONACCESS
#define ELYSIUM_CORE_SERVICEPROCESS_SERVICECONTROLLERPERMISSIONACCESS

namespace Elysium
{
	namespace Core
	{
		namespace ServiceProcess
		{
			enum class ServiceControllerPermissionAccess : int
			{
				None = 0,
				Browse = 2,
				Control = 6,
			};
		}
	}
}
#endif
