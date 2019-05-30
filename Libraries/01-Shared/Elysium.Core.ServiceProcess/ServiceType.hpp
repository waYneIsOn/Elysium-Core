/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_SERVICEPROCESS_SERVICETYPE
#define ELYSIUM_CORE_SERVICEPROCESS_SERVICETYPE

namespace Elysium
{
	namespace Core
	{
		namespace ServiceProcess
		{
			enum class ServiceType : int
			{
				KernelDriver = 1,
				FileSystemDriver = 2,
				Adapter = 4,
				RecognizerDriver = 8,
				Win32OwnProcess = 16,
				Win32ShareProcess = 32,
				InteractiveProcess = 256,
			};
		}
	}
}
#endif
