/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_THREADING_TASKS_ATOMICOFTASKSTATUS
#define ELYSIUM_CORE_THREADING_TASKS_ATOMICOFTASKSTATUS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_ATOMIC
#include "../../Elysium.Core.Template/Atomic.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_TASKS_TASKSTATUS
#include "../TaskStatus.hpp"
#endif

namespace Elysium::Core::Threading::Tasks
{
	template class ELYSIUM_CORE_API Elysium::Core::Template::Threading::Atomic<TaskStatus>;

	using AtomicOfTaskStatus = Elysium::Core::Template::Threading::Atomic<TaskStatus>;
}
#endif
