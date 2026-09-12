/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_INTERLOCKED
#define ELYSIUM_CORE_TEMPLATE_THREADING_INTERLOCKED

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_INTERLOCKED_WINDOWS
#include "Interlocked.Windows.hpp"
#endif
#endif

#endif
