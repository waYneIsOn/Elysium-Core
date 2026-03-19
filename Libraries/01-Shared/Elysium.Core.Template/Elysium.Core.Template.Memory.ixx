module;

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

export module Elysium.Core.Template.Memory;

export
{
	using Elysium::Core::Template::Memory::Activator;
	using Elysium::Core::Template::Memory::DefaultAllocator;
	using Elysium::Core::Template::Memory::DefaultDeleter;
	using Elysium::Core::Template::Memory::MAllocator;
	using Elysium::Core::Template::Memory::MemCmp;
	using Elysium::Core::Template::Memory::MemCpy;
	using Elysium::Core::Template::Memory::MemoryOrder;
	using Elysium::Core::Template::Memory::MemSet;
	using Elysium::Core::Template::Memory::ObserverPointer;
	//using Elysium::Core::Template::Memory::SharedPointer;
	using Elysium::Core::Template::Memory::UniquePointer;
	//using Elysium::Core::Template::Memory::WeakPointer;
}
