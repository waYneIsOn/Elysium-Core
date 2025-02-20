/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY
#define ELYSIUM_CORE_TEMPLATE_MEMORY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_DEFAULTALLOCATOR
#include "DefaultAllocator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MALLOCATOR
#include "MAllocator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMCMP
#include "MemCmp.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMCPY
#include "MemCpy.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMORYORDER
#include "MemoryOrder.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMSET
#include "MemSet.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_SCOPED
#include "Memory/Scoped.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_SHAREDPOINTER
#include "SharedPointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_UNIQUEPOINTER
#include "UniquePointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_WEAKPOINTER
#include "WeakPointer.hpp"
#endif

#endif