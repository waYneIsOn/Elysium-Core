/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_STACKTRACE
#define ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_STACKTRACE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_STACKTRACE_WINDOWS
#include "StackTrace.Windows.hpp"
#endif
#endif

#endif
