/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMORYORDER
#define ELYSIUM_CORE_TEMPLATE_MEMORY_MEMORYORDER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

namespace Elysium::Core::Template::Memory
{
    /// <summary>
    /// Specifies how memory accesses, including regular, non-atomic memory accesses, are to be ordered around an atomic operation.
    /// Absent any constraints on a multi-core system, when multiple threads simultaneously read and write to several variables,
    /// one thread can observe the values change in an order different from the order another thread wrote them.
    /// Indeed, the apparent order of changes can even differ among multiple reader threads.
    /// Some similar effects can occur even on uniprocessor systems due to compiler transformations allowed by the memory model.
    /// 
    /// Read:
    /// https://en.wikipedia.org/wiki/Memory_ordering
    /// https://www.freecodecamp.org/news/atomics-and-concurrency-in-cpp/
    /// https://www.sobyte.net/post/2022-06/cpp-memory-order/
    /// https://stackoverflow.com/questions/12346487/what-do-each-memory-order-mean
    /// </summary>
    enum class MemoryOrder
        : Elysium::Core::Template::System::int32_t
    {
        /// <summary>
        /// There are no synchronization or ordering constraints imposed on other reads or writes, only this operation's atomicity is guaranteed.
        /// </summary>
        Relaxed,

        /// <summary>
        /// A load operation with this memory order performs a consume operation on the affected memory location:
        /// No reads or writes in the current thread dependent on the value currently loaded can be reordered before this load. 
        /// Writes to data-dependent variables in other threads that release the same atomic variable are visible in the current thread.
        /// On most platforms, this affects compiler optimizations only
        /// </summary>
        Consume,

        /// <summary>
        /// A load operation with this memory order performs the acquire operation on the affected memory location:
        /// No reads or writes in the current thread can be reordered before this load. 
        /// All writes in other threads that release the same atomic variable are visible in the current thread.
        /// </summary>
        Acquire,

        /// <summary>
        /// A store operation with this memory order performs the release operation:
        /// No reads or writes in the current thread can be reordered after this store.
        /// All writes in the current thread are visible in other threads that acquire the same atomic variable (see Release-Acquire ordering below) and
        /// writes that carry a dependency into the atomic variable become visible in other threads that consume the same atomic.
        /// </summary>
        Release,

        /// <summary>
        /// A read-modify-write operation with this memory order is both an acquire operation and a release operation.
        /// No memory reads or writes in the current thread can be reordered before the load, nor after the store.
        /// All writes in other threads that release the same atomic variable are visible before the modification and 
        /// the modification is visible in other threads that acquire the same atomic variable. 
        /// </summary>
        AcquireRelease,

        /// <summary>
        /// A load operation with this memory order performs an acquire operation, a store performs a release operation, and 
        /// read-modify-write performs both an acquire operation and a release operation, plus a single total order exists 
        /// in which all threads observe all modifications in the same order.
        /// </summary>
        SequentiallyConsistent
    };
}
#endif
