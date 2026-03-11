module;

export module Elysium.Core.Template.Memory;

export
{
#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_ACTIVATOR
#include "Memory/Activator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_DEFAULTALLOCATOR
#include "Memory/DefaultAllocator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_DEFAULTDELETER
#include "Memory/DefaultDeleter.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MALLOCATOR
#include "Memory/MAllocator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMCMP
#include "Memory/MemCmp.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMCPY
#include "Memory/MemCpy.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMORYORDER
#include "Memory/MemoryOrder.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMSET
#include "Memory/MemSet.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_OBSERVERPOINTER
#include "Memory/ObserverPointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_SHAREDPOINTER
#include "Memory/SharedPointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_UNIQUEPOINTER
#include "Memory/UniquePointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_WEAKPOINTER
#include "Memory/WeakPointer.hpp"
#endif
}
