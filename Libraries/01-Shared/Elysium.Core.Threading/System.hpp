/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_THREADING_SYSTEM
#define ELYSIUM_CORE_THREADING_SYSTEM

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

#if defined(ELYSIUM_CORE_OS_WINDOWS)

#ifndef _WINDOWS_
#define _WINSOCKAPI_ // don't include winsock
#include <Windows.h>
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

#define ELYSIUM_THREAD_GETCURRENTTHREADID GetCurrentThreadId

// Thread Pool
#define ELYSIUM_THREADPOOL_HANDLE PTP_POOL
#define ELYSIUM_THREADPOOL_CREATE CreateThreadpool
#define ELYSIUM_THREADPOOL_SET_THREAD_MAXIMUM SetThreadpoolThreadMaximum
#define ELYSIUM_THREADPOOL_SET_THREAD_MINIMUM SetThreadpoolThreadMinimum
#define ELYSIUM_THREADPOOL_CLOSE CloseThreadpool

// Thread Pool - Environment
#define ELYSIUM_THREADPOOL_ENVIRONMENT TP_CALLBACK_ENVIRON_V3
#define ELYSIUM_THREADPOOL_ENVIRONMENT_INITIALIZE InitializeThreadpoolEnvironment
#define ELYSIUM_THREADPOOL_SET_CALLBACK_POOL SetThreadpoolCallbackPool
#define ELYSIUM_THREADPOOL_SET_CALLBACK_LIBRARY SetThreadpoolCallbackLibrary
#define ELYSIUM_THREADPOOL_ENVIRONMENT_DESTROY DestroyThreadpoolEnvironment

// Thread Pool - Cleanup Group
#define ELYSIUM_THREADPOOL_CLEANUPGROUP_HANDLE PTP_CLEANUP_GROUP
#define ELYSIUM_THREADPOOL_CLEANUPGROUP_CREATE CreateThreadpoolCleanupGroup
#define ELYSIUM_THREADPOOL_SET_CALLBACK_CLEANUPGROUP SetThreadpoolCallbackCleanupGroup
#define ELYSIUM_THREADPOOL_CLEANUPGROUP_CLOSE_MEMBERS CloseThreadpoolCleanupGroupMembers
#define ELYSIUM_THREADPOOL_CLEANUPGROUP_CLOSE CloseThreadpoolCleanupGroup

// Task
#define ELYSIUM_TASK_HANDLE PTP_WORK
#define ELYSIUM_TASK_CREATE CreateThreadpoolWork
#define ELYSIUM_TASK_SUBMIT SubmitThreadpoolWork
#define ELYSIUM_TASK_TRY_SUBMIT TrySubmitThreadpoolCallback 
#define ELYSIUM_TASK_AWAIT_CALLBACK WaitForThreadpoolWorkCallbacks
#define ELYSIUM_TASK_CLOSE CloseThreadpoolWork

#define ELYSIUM_TASK_CALLBACK_HANDLE PTP_WORK_CALLBACK
#define ELYSIUM_TASK_CALLBACK_INSTANCE PTP_CALLBACK_INSTANCE

//#define BLA CreateThreadpoolWait
/*
// Task - IOCompletionPort (used in Elysium::Core::Net and not here)
#define ELYSIUM_THREADPOOL_IO_HANDLE PTP_IO
#define ELYSIUM_THREADPOOL_IO_CREATE CreateThreadpoolIo
#define ELYSIUM_THREADPOOL_IO_START StartThreadpoolIo
#define ELYSIUM_THREADPOOL_IO_WAIT_FOR_CALLBACKS WaitForThreadpoolIoCallbacks
#define ELYSIUM_THREADPOOL_IO_CANCEL CancelThreadpoolIo
#define ELYSIUM_THREADPOOL_IO_CLOSE CloseThreadpoolIo
/*
// io completion port - old API
#define ELYSIUM_IOCOMPLETIONPORT_HANDLE HANDLE
#define ELYSIUM_IOCOMPLETIONPORT_CREATE CreateIoCompletionPort
#define ELYSIUM_IOCOMPLETIONPORT_BIND_CALLBACK BindIoCompletionCallback
#define ELYSIUM_IOCOMPLETIONPORT_POST_QUEUED_COMPLETION_STATUS PostQueuedCompletionStatus
#define ELYSIUM_IOCOMPLETIONPORT_GET_QUEUED_COMPLETION_STATUS GetQueuedCompletionStatus
*/
#elif defined(ELYSIUM_CORE_OS_ANDROID)

// Any synchronization primitive
#define ELYSIUM_SYNCHRONIZATION_PRIMITIVE_HANDLE void*

#elif defined(ELYSIUM_CORE_OS_LINUX)

#elif defined(ELYSIUM_CORE_OS_MAC)

#else
#error "unsupported os"
#endif
#endif
