/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DIAGNOSTICS_SYSTEM
#define ELYSIUM_CORE_DIAGNOSTICS_SYSTEM

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../Elysium.Core.Template/System/OperatingSystem.hpp"
#endif

#if defined(ELYSIUM_CORE_OS_WINDOWS)
#ifndef _WINDOWS_
//#define _WINSOCKAPI_ // don't include winsock
#define WIN32_LEAN_AND_MEAN
//#include <Windows.h>
#endif

#ifndef _PROCESSTHREADSAPI_H_
#include <processthreadsapi.h>
#endif

#define ELYSIUM_CORE_DIAGNOSTICS_PROCESSHANDLE HANDLE
#define ELYSIUM_CORE_DIAGNOSTICS_GETCURRENTPROCESS GetCurrentProcess
#define ELYSIUM_CORE_DIAGNOSTICS_GETPROCESSBYID OpenProcess
#define ELYSIUM_CORE_DIAGNOSTICS_GETPROCESSID GetProcessId 
#elif defined(ELYSIUM_CORE_OS_ANDROID)

#else
#error "undefined os"
#endif

#endif
