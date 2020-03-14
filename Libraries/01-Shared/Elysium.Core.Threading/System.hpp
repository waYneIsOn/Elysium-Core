/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_THREADING_SYSTEM
#define ELYSIUM_CORE_THREADING_SYSTEM

#if defined(_WIN32) || defined(_WIN64) ||  defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__) || defined(__CYGWIN__)

#ifndef _WINNT_
#define _WINSOCKAPI_ // don't include winsock
#include <Windows.h>
#endif

#ifndef _SYNCHAPI_H_
#include <synchapi.h>
#endif

// Any synchronization primitive
#define ELYSIUM_SYNCHRONIZATION_PRIMITIVE_HANDLE HANDLE
#define ELYSIUM_SYNCHRONIZATION_PRIMITIVE_DESTROY CloseHandle
#define ELYSIUM_SYNCHRONIZATION_PRIMITIVE_WAIT_FOR_SINGLE_OBJECT WaitForSingleObject
//#define ELYSIUM_SYNCHRONIZATION_PRIMITIVE_WAIT_FOR_MULTIPLE_OBJECTS WaitForMultipleObjects
#define ELYSIUM_SYNCHRONIZATION_PRIMITIVE_WAIT_FOR_MULTIPLE_OBJECTS_EX WaitForMultipleObjectsEx

// Critical section (lightweight "mutexes" which - as opposed to mutexes - cannot be shared across multiple processes (making them faster/more lightweight))
#define ELYSIUM_CRITICAL_SECTION_HANDLE CRITICAL_SECTION
#define ELYSIUM_CRITICAL_SECTION_CREATE InitializeCriticalSection
//#define ELYSIUM_CRITICAL_SECTION_CREATEEX InitializeCriticalSectionEx
#define ELYSIUM_CRITICAL_SECTION_DESTROY DeleteCriticalSection

#define ELYSIUM_CRITICAL_SECTION_TRYENTER TryEnterCriticalSection
#define ELYSIUM_CRITICAL_SECTION_ENTER EnterCriticalSection

#define ELYSIUM_CRITICAL_SECTION_LEAVE LeaveCriticalSection

// Interlocked
#define ELYSIUM_INTERLOCKED_ADD InterlockedAdd
#define ELYSIUM_INTERLOCKED_ADD64 InterlockedAdd64

#define ELYSIUM_INTERLOCKED_COMPARE_EXCHANGE InterlockedCompareExchange
#define ELYSIUM_INTERLOCKED_COMPARE_EXCHANGE64 InterlockedCompareExchange64

#define ELYSIUM_INTERLOCKED_DECREMENT InterlockedDecrement
#define ELYSIUM_INTERLOCKED_DECREMENT64 InterlockedDecrement64

#define ELYSIUM_INTERLOCKED_INCREMENT InterlockedIncrement
#define ELYSIUM_INTERLOCKED_INCREMENT64 InterlockedIncrement64

// Mutex
#define ELYSIUM_MUTEX_CREATE CreateMutex

#define ELYSIUM_MUTEX_UNLOCK ReleaseMutex

// Semaphore
#define ELYSIUM_SEMAPHORE_CREATE CreateSemaphore
//#define ELYSIUM_SEMAPHORE_CREATE_EX CreateSemaphoreEx

#define ELYSIUM_SEMAPHORE_RELEASE ReleaseSemaphore

// Signal
#define ELYSIUM_SIGNAL_CREATE CreateEvent
//#define ELYSIUM_SIGNAL_CREATE_EX CreateEventEx

#define ELYSIUM_SIGNAL_RAISE SetEvent

#define ELYSIUM_SIGNAL_CLEAR ResetEvent

// Thread
#define ELYSIUM_THREAD_CREATE CreateThread

#define ELYSIUM_THREAD_SETPRIORITY SetThreadPriority

#define ELYSIUM_THREAD_SLEEP SleepEx

#elif defined(__ANDROID__)

#elif defined(linux) || defined(__linux) || defined(__linux__) || defined(__gnu_linux__))

#elif defined(macintosh) || defined(Macintosh) || (defined(__APPLE__) && defined(__MACH__)))

#else
#error "unsupported os"
#endif
#endif
