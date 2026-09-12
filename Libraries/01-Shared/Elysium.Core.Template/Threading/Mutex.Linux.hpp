/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_MUTEX_LINUX
#define ELYSIUM_CORE_TEMPLATE_THREADING_MUTEX_LINUX

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_LINUX
#ifndef _PTHREAD_H
#include <pthread.h>
#endif

namespace Elysium::Core::Template::Threading
{
    /// <summary>
    /// A synchronization primitive that can also be used for interprocess synchronization.
    /// </summary>
    class Mutex final
        : public WaitHandle
    {
    public:
        inline constexpr Mutex(const bool InitiallyOwned = false, const char8_t* Name = nullptr)
            : WaitHandle(PTHREAD_MUTEX_INITIALIZER)
        {
            if (InitiallyOwned)
            {
                pthread_mutex_lock(&_Handle);
            }
        }

        constexpr Mutex(const Mutex& Source) = delete;

        constexpr Mutex(Mutex&& Right) noexcept = delete;

        inline constexpr virtual ~Mutex() override
        {
            // @ToDo: Parent destructor will call Close(). Do I need to release here beforehand though? need to write specific test!
        }
    public:
        constexpr Mutex& operator=(const Mutex& Source) = delete;

        constexpr Mutex& operator=(Mutex&& Right) noexcept = delete;
    public:
        inline void Lock()
        {}

        //bool TryLock();

        inline void Unlock()
        {}
    };
    /*
    inline void Elysium::Core::Template::Threading::Mutex::Release()
    {
        int WasReleased = pthread_mutex_unlock(&_Handle);
    }
    */
}
#endif
#endif