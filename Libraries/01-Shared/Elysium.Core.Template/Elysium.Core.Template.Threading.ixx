module;

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif
#else
#error "unsupported os"
#endif

#ifndef _ASSERT_OK
#include <cassert>
#define _ASSERT_OK	// defined so Elysium::Core::Template::Memory::Scoped::Arena include works without warning C5244
#endif

#ifndef _NEW_
#include <new>
#endif

#ifndef _INC_PROCESS
#include <process.h>
#endif

#ifndef _INITIALIZER_LIST_
#include <initializer_list>
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_ATOMICBASE
#include "Threading/_AtomicBase.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_ATOMICENUM
#include "Threading/_AtomicEnum.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_ATOMICINTEGRAL
#include "Threading/_AtomicIntegral.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_ATOMICPOINTER
#include "Threading/_AtomicPointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_ATOMIC
#include "Threading/Atomic.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_AUTORESETEVENT
#include "Threading/AutoResetEvent.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_CALLONCE
#include "Threading/CallOnce.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_CRITICALSECTION
#include "Threading/CriticalSection.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_EVENTWAITHANDLE
#include "Threading/EventWaitHandle.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_FIBER
#include "Threading/Fiber.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_MANUALRESETEVENT
#include "Threading/ManualResetEvent.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_INTERLOCKED
#include "Threading/Interlocked.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_MUTEX
#include "Threading/Mutex.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_SEMAPHORE
#include "Threading/Semaphore.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_SHAREDMUTEX
#include "Threading/SharedMutex.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_THREAD
#include "Threading/Thread.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_THREADPOOL
#include "Threading/ThreadPool.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_WAITHANDLE
#include "Threading/WaitHandle.hpp"
#endif

export module Elysium.Core.Template.Threading;

export
{
	using Elysium::Core::Template::Threading::_AtomicBase;
	using Elysium::Core::Template::Threading::_AtomicEnum;
	using Elysium::Core::Template::Threading::_AtomicIntegral;
	using Elysium::Core::Template::Threading::_AtomicPointer;
	using Elysium::Core::Template::Threading::Atomic;
	using Elysium::Core::Template::Threading::AutoResetEvent;
	using Elysium::Core::Template::Threading::CallOnce;
	using Elysium::Core::Template::Threading::CriticalSection;
	using Elysium::Core::Template::Threading::EventWaitHandle;
	using Elysium::Core::Template::Threading::Fiber;
	using Elysium::Core::Template::Threading::ManualResetEvent;
	using Elysium::Core::Template::Threading::Interlocked;
	using Elysium::Core::Template::Threading::Mutex;
	using Elysium::Core::Template::Threading::Semaphore;
	using Elysium::Core::Template::Threading::SharedMutex;
	using Elysium::Core::Template::Threading::Thread;
	using Elysium::Core::Template::Threading::ThreadPool;
	using Elysium::Core::Template::Threading::WaitHandle;
}
