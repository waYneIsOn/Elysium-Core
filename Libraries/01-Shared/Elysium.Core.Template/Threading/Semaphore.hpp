/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_SEMAPHORE
#define ELYSIUM_CORE_TEMPLATE_THREADING_SEMAPHORE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_SEMAPHORE_WINDOWS
#include "Semaphore.Windows.hpp"
#endif
#endif

#endif
