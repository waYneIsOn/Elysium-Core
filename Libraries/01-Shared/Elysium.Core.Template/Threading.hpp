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
#include "AtomicBase.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_ATOMICINTEGRAL
#include "AtomicIntegral.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_ATOMICPOINTER
#include "AtomicPointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_AUTORESETEVENT
#include "AutoResetEvent.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_CRITICALSECTION
#include "CriticalSection.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_EVENTWAITHANDLE
#include "EventWaitHandle.hpp"
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

#ifndef ELYSIUM_CORE_THREADING_WAITHANDLE
#include "WaitHandle.hpp"
#endif

#endif
