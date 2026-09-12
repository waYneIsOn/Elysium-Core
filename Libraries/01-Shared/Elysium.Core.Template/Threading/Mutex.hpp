/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_MUTEX
#define ELYSIUM_CORE_TEMPLATE_THREADING_MUTEX

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_MUTEX_WINDOWS
#include "Mutex.Windows.hpp"
#endif
#elif defined ELYSIUM_CORE_OS_LINUX
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_MUTEX_LINUX
#include "Mutex.Linux.hpp"
#endif
#endif

#endif
