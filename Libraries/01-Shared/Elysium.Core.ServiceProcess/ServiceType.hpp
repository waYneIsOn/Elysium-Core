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

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::ServiceProcess
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class ServiceType : uint32_t
#elif defined(__ANDROID__)
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
		InteractiveProcess = 256,
	};
}
#endif
