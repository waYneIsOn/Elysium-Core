/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_WAITHANDLE
#define ELYSIUM_CORE_TEMPLATE_THREADING_WAITHANDLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_WAITHANDLE_WINDOWS
#include "WaitHandle.Windows.hpp"
#endif
#elif defined (ELYSIUM_CORE_OS_LINUX) || defined (ELYSIUM_CORE_OS_ANDROID)
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_WAITHANDLE_LINUX
#include "WaitHandle.Linux.hpp"
#endif
#endif

#endif
