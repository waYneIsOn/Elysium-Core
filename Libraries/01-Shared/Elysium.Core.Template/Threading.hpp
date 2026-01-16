/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING
#define ELYSIUM_CORE_TEMPLATE_THREADING

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_ATOMIC
#include "Atomic.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_ATOMICBASE
#include "_AtomicBase.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_ATOMICENUM
#include "Threading/_AtomicEnum.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_ATOMICINTEGRAL
#include "_AtomicIntegral.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_ATOMICPOINTER
#include "_AtomicPointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_AUTORESETEVENT
#include "AutoResetEvent.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_CALLONCE
#include "Threading/CallOnce.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_CRITICALSECTION
#include "CriticalSection.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_EVENTWAITHANDLE
#include "EventWaitHandle.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_FIBER
#include "Threading/Fiber.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_MANUALRESETEVENT
#include "ManualResetEvent.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_INTERLOCKED
#include "Interlocked.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_MUTEX
#include "Mutex.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_SEMAPHORE
#include "Semaphore.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_SHAREDMUTEX
#include "SharedMutex.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_THREAD
#include "Threading/Thread.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_THREADPOOL
#include "Threading/ThreadPool.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_WAITHANDLE
#include "WaitHandle.hpp"
#endif

#endif
