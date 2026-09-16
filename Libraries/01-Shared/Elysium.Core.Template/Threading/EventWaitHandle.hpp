/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_EVENTWAITHANDLE
#define ELYSIUM_CORE_TEMPLATE_THREADING_EVENTWAITHANDLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_EVENTWAITHANDLE_WINDOWS
#include "EventWaitHandle.Windows.hpp"
#endif
#elif defined (ELYSIUM_CORE_OS_LINUX) || defined (ELYSIUM_CORE_OS_ANDROID)
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_EVENTWAITHANDLE_LINUX
#include "EventWaitHandle.Linux.hpp"
#endif
#endif

#endif
