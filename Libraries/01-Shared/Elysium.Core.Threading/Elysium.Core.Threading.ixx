module;

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../Elysium.Core.Template/System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
//import <Windows.h>;
#endif
#else
#error "unsupported os"
#endif

#ifndef _CMATH_
// @ToDo: Elysium::Core::Template::Math::Logarithm
#include <cmath>
#endif

#ifndef _INITIALIZER_LIST_
#include <initializer_list>
#endif

#ifndef _LIMITS_
#include <limits>
#endif

#ifndef _NEW_
#include <new>
#endif

export module Elysium.Core.Threading;

export
{
/*
#ifndef ELYSIUM_CORE_THREADING_ATOMIC
#include "Atomic.hpp"
#endif
*/
	/*
#ifndef ELYSIUM_CORE_THREADING_THREAD
#include "Thread.hpp"
#endif
	*/
/*
#ifndef ELYSIUM_CORE_THREADING_THREADPOOL
#include "ThreadPool.hpp"
#endif
*/
}
