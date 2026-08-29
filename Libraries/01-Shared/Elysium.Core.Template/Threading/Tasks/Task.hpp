/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_TASKS_TASK
#define ELYSIUM_CORE_TEMPLATE_THREADING_TASKS_TASK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
	#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_TASKS_TASK_WINDOWS
	#include "Task.Windows.hpp"
	#endif
#endif
#endif
