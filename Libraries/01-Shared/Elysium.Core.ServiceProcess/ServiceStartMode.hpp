/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_SERVICEPROCESS_SERVICESTARTMODE
#define ELYSIUM_CORE_SERVICEPROCESS_SERVICESTARTMODE

namespace Elysium
{
	namespace Core
	{
		namespace ServiceProcess
		{
			enum class ServiceStartMode : int
			{
				Boot = 0,
				System = 1,
				Automatic = 2,
				Manual = 3,
				Disabled = 4,
			};

			inline ServiceStartMode operator|(ServiceStartMode lhs, ServiceStartMode rhs)
			{
				return static_cast<ServiceStartMode>(static_cast<int>(lhs) | static_cast<int>(rhs));
			}
			inline ServiceStartMode operator&(ServiceStartMode lhs, ServiceStartMode rhs)
			{
				return static_cast<ServiceStartMode>(static_cast<int>(lhs) & static_cast<int>(rhs));
			}
		}
	}
}
#endif
