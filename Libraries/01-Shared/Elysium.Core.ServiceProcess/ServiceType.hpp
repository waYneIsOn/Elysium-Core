/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SERVICEPROCESS_SERVICETYPE
#define ELYSIUM_CORE_SERVICEPROCESS_SERVICETYPE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../Elysium.Core.Template/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../Elysium.Core.Template/Primitives.hpp"
#endif

namespace Elysium::Core::ServiceProcess
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class ServiceType : Elysium::Core::Template::System::uint16_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class ServiceType
#else
#error "undefined os"
#endif
	{
		KernelDriver = 1,

		FileSystemDriver = 2,

		Adapter = 4,

		RecognizerDriver = 8,

		Win32OwnProcess = 16,

		Win32ShareProcess = 32,

		InteractiveProcess = 256
	};
}
#endif
