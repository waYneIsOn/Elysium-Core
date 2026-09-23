/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_TASKS_TASK_WINDOWS
#define ELYSIUM_CORE_TEMPLATE_THREADING_TASKS_TASK_WINDOWS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef ELYSIUM_CORE_TEMPLATE_COROUTINES_COROUTINECONTINUATIONSTATE
#include "../../Coroutines/CoroutineContinuationState.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_COROUTINES_COROUTINEHANDLE
#include "../../Coroutines/CoroutineHandle.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_COROUTINES_AWAITER_DELEGATEAWAITER
#include "../../Coroutines/Awaiter/DelegateAwaiter.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_COROUTINES_AWAITER_FINALAWAITER
#include "../../Coroutines/Awaiter/FinalAwaiter.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_COROUTINES_AWAITER_SUSPENDALWAYS
#include "../../Coroutines/Awaiter/SuspendAlways.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_COROUTINES_AWAITER_SUSPENDNEVER
#include "../../Coroutines/Awaiter/SuspendNever.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_COROUTINES_AWAITER_TASKAWAITER
#include "../../Coroutines/Awaiter/TaskAwaiter.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_IO_IOEXCEPTION
#include "../../Exceptions/IO/IOException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "../../Text/String.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_ATOMIC
#include "../../Threading/Atomic.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_MANUALRESETEVENT
#include "../../Threading/ManualResetEvent.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_TASKS_TASKSTATUS
#include "TaskStatus.hpp"
#endif

#ifndef _MINWINBASE_
#include <minwinbase.h>
#endif

#ifndef _MINWINDEF_
#include <minwindef.h>
#endif

namespace Elysium::Core::Template::IO::Device
{
    class FileDevice;
}

namespace UnitTests::Core::Template::Threading::Tasks
{
    class TaskTests;
}

namespace Elysium::Core::Template::Threading::Tasks
{
    template <class Result>
    class Task
    {
    public:
        friend class Elysium::Core::Template::IO::Device::FileDevice;
        friend class Elysium::Core::Template::Coroutines::Awaiter::TaskAwaiter<Result>;
    public:
        struct promise_type
        {
        public:
            friend class Task<Result>;
            friend class Elysium::Core::Template::IO::Device::FileDevice;

            template <class Promise, class ReturnType, class ...Args>
            friend class Elysium::Core::Template::Coroutines::Awaiter::DelegateAwaiter;

            friend class Elysium::Core::Template::Coroutines::Awaiter::TaskAwaiter<Result>;

            friend class UnitTests::Core::Template::Threading::Tasks::TaskTests;
        public:
            Task<Result> get_return_object()
            {
                OutputDebugStringA("promise_type<Result>::get_return_object() creating Task<Result>\r\n");
                return Task<Result>(*this);
            }

            Elysium::Core::Template::Coroutines::Awaiter::SuspendNever initial_suspend()
            {
                return {};
            }

            Elysium::Core::Template::Coroutines::Awaiter::FinalAwaiter final_suspend() noexcept
            {
                OutputDebugStringA("Task<Result>::final_suspend() creating FinalAwaiter\r\n");

                _Status = Elysium::Core::Template::Threading::Tasks::TaskStatus::RanToCompletion;

                if (!_ManagedExternally)
                {
                    _CoroutineCompletionEvent.Set();
                }

                return Elysium::Core::Template::Coroutines::Awaiter::FinalAwaiter(CompleteTask());
            }
            
            void return_value(Result Value)
            {
                _Result = Value;
            }
            /*
            void yield_value(Result Value)
            { }
            */
            void unhandled_exception()
            {
                std::exception_ptr Exception = std::current_exception();

                try
                {
                    std::rethrow_exception(Exception);
                }
                catch (const Elysium::Core::Template::Exceptions::IO::IOException& Ex)
                {
                    bool sdf = false;
                }
                catch (const Elysium::Core::Template::Exceptions::Exception& Ex)
                {
                    bool sdf = false;
                }

                bool sdfsdf = false;
            }
        private:
            Elysium::Core::Template::Coroutines::CoroutineHandle<> CompleteTask() noexcept
            {
                Elysium::Core::Template::Coroutines::CoroutineContinuationState Expected = Elysium::Core::Template::Coroutines::CoroutineContinuationState::Pending;

                // No waiter has registered yet
                if (_ContinuationState.CompareExchangeStrong(Expected, Elysium::Core::Template::Coroutines::CoroutineContinuationState::Completed,
                    Elysium::Core::Template::Memory::MemoryOrder::AcquireRelease, Elysium::Core::Template::Memory::MemoryOrder::Acquire))
                {
                    return std::noop_coroutine();
                }

                // ...
                _ContinuationState.Store(Elysium::Core::Template::Coroutines::CoroutineContinuationState::Completed, Elysium::Core::Template::Memory::MemoryOrder::Release);

                return _OuterCoroutineHandle;
            }
        private:
            OVERLAPPED _Overlapped{};

            Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::Threading::Tasks::TaskStatus> _Status{};
            Elysium::Core::Template::Threading::Atomic<bool> _HasCompletedSynchronously{};
            DWORD _ErrorCode{};
            Result _Result{};

            bool _ManagedExternally{};
            Elysium::Core::Template::Threading::ManualResetEvent _CoroutineCompletionEvent{};

            Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::Coroutines::CoroutineContinuationState> _ContinuationState{};
            Elysium::Core::Template::Coroutines::CoroutineHandle<> _OuterCoroutineHandle{};    // continuation/who awaits this frame?
        public:
            Elysium::Core::Template::Text::String<char> _Name{};
        };
    public:
        using PromiseType = promise_type;
        using CoroutineHandleType = Elysium::Core::Template::Coroutines::CoroutineHandle<PromiseType>;
    public:
        constexpr Task() noexcept = delete;
    private:
        inline explicit constexpr Task(PromiseType& Promise) noexcept
            : _Promise(Promise), _CoroutineFrameHandle(Elysium::Core::Template::Coroutines::CoroutineHandle<promise_type>::FromPromise(Promise))
        { }
    public:
        constexpr Task(const Task& Source) noexcept = delete;

        constexpr Task(Task&& Right) noexcept = delete;

        inline ~Task() noexcept
        {
            OutputDebugStringA("Task<Result>::~Task\r\n");

            if (_Promise._ManagedExternally)
            {
                return;
            }

            if (_CoroutineFrameHandle)
            {
                _CoroutineFrameHandle.destroy();
            }
        }
    public:
        constexpr Task& operator=(const Task& Source) noexcept = delete;

        constexpr Task& operator=(Task&& Right) noexcept = delete;
    public:
        Elysium::Core::Template::Coroutines::Awaiter::TaskAwaiter<Result> operator co_await() noexcept
        {
            OutputDebugStringA("Task<Result>::operator co_await()\r\n");
            return Elysium::Core::Template::Coroutines::Awaiter::TaskAwaiter<Result>(*this);
        }
    public:
        inline constexpr const bool GetIsCompleted() const noexcept
        {
            return Elysium::Core::Template::Threading::Tasks::TaskStatus::RanToCompletion == _Promise._Status;
        }

        inline Elysium::Core::Template::System::uint16_t GetErrorCode() const noexcept
        {
            return _Promise._ErrorCode;
        }

        inline Result GetResult()
        {
            return _Promise._Result;
        }
    public:
        inline Task<Result>& Wait()
        {
            const bool WaitResult = _Promise._CoroutineCompletionEvent.WaitOne();
            if (!WaitResult)
            {
                bool sdf = false;
            }

            return *this;
        }
    private:
        PromiseType& _Promise;
        CoroutineHandleType _CoroutineFrameHandle;
    };
    
    /// <summary>
    /// 
    /// </summary>
    template <>
    class Task<void>
    {
    public:
        friend class Elysium::Core::Template::IO::Device::FileDevice;
        friend class Elysium::Core::Template::Coroutines::Awaiter::TaskAwaiter<void>;
    public:
        struct promise_type
        {
        public:
            friend class Task;
            friend class Elysium::Core::Template::IO::Device::FileDevice;

            template <class Promise, class ReturnType, class ...Args>
            friend class Elysium::Core::Template::Coroutines::Awaiter::DelegateAwaiter;

            friend class Elysium::Core::Template::Coroutines::Awaiter::TaskAwaiter<void>;

            friend class UnitTests::Core::Template::Threading::Tasks::TaskTests;
        public:
            Task<void> get_return_object()
            {
                OutputDebugStringA("promise_type<void>::get_return_object() creating Task<void>\r\n");
                return Task<void>(*this);
            }

            Elysium::Core::Template::Coroutines::Awaiter::SuspendNever initial_suspend()
            {
                return {};
            }

            Elysium::Core::Template::Coroutines::Awaiter::FinalAwaiter final_suspend() noexcept
            {
                OutputDebugStringA("Task<void>::final_suspend() creating FinalAwaiter\r\n");

                _Status = Elysium::Core::Template::Threading::Tasks::TaskStatus::RanToCompletion;

                if (!_ManagedExternally)
                {
                    _CoroutineCompletionEvent.Set();
                }

                return Elysium::Core::Template::Coroutines::Awaiter::FinalAwaiter(CompleteTask());
            }
            
            void return_void()
            { }
           
            void unhandled_exception()
            {
                std::exception_ptr Exception = std::current_exception();

                try
                {
                    std::rethrow_exception(Exception);
                }
                catch (const Elysium::Core::Template::Exceptions::IO::IOException& Ex)
                {
                    bool sdf = false;
                }
                catch (const Elysium::Core::Template::Exceptions::Exception& Ex)
                {
                    bool sdf = false;
                }

                bool sdfsdf = false;
            }
        private:
            Elysium::Core::Template::Coroutines::CoroutineHandle<> CompleteTask() noexcept
            {
                Elysium::Core::Template::Coroutines::CoroutineContinuationState Expected = Elysium::Core::Template::Coroutines::CoroutineContinuationState::Pending;

                // No waiter has registered yet
                if (_ContinuationState.CompareExchangeStrong(Expected, Elysium::Core::Template::Coroutines::CoroutineContinuationState::Completed,
                    Elysium::Core::Template::Memory::MemoryOrder::AcquireRelease, Elysium::Core::Template::Memory::MemoryOrder::Acquire))
                {
                    return std::noop_coroutine();
                }

                // ...
                _ContinuationState.Store(Elysium::Core::Template::Coroutines::CoroutineContinuationState::Completed, Elysium::Core::Template::Memory::MemoryOrder::Release);

                return _OuterCoroutineHandle;
            }
        private:
            OVERLAPPED _Overlapped{};

            Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::Threading::Tasks::TaskStatus> _Status{};
            Elysium::Core::Template::Threading::Atomic<bool> _HasCompletedSynchronously{};
            DWORD _ErrorCode{};

            bool _ManagedExternally{};
            Elysium::Core::Template::Threading::ManualResetEvent _CoroutineCompletionEvent{};

            Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::Coroutines::CoroutineContinuationState> _ContinuationState{};
            Elysium::Core::Template::Coroutines::CoroutineHandle<> _OuterCoroutineHandle{};    // continuation/who awaits this frame?
        public:
            Elysium::Core::Template::Text::String<char> _Name{};
        };
    public:
        using PromiseType = promise_type;
        using CoroutineHandleType = Elysium::Core::Template::Coroutines::CoroutineHandle<PromiseType>;
    public:
        constexpr Task() noexcept = delete;
    private:
        inline explicit constexpr Task(PromiseType& Promise) noexcept
            : _Promise(Promise), _CoroutineFrameHandle(Elysium::Core::Template::Coroutines::CoroutineHandle<promise_type>::FromPromise(Promise))
        { }
    public:
        constexpr Task(const Task& Source) noexcept = delete;

        constexpr Task(Task&& Right) noexcept = delete;

        inline ~Task() noexcept
        {
            OutputDebugStringA("Task<void>::~Task\r\n");

            if (_Promise._ManagedExternally)
            {
                return;
            }

            if (_CoroutineFrameHandle)
            {
                _CoroutineFrameHandle.destroy();
            }
        }
    public:
        constexpr Task& operator=(const Task& Source) noexcept = delete;

        constexpr Task& operator=(Task&& Right) noexcept = delete;
    public:
        Elysium::Core::Template::Coroutines::Awaiter::TaskAwaiter<void> operator co_await() noexcept
        {
            OutputDebugStringA("Task<void>::operator co_await()\r\n");
            return Elysium::Core::Template::Coroutines::Awaiter::TaskAwaiter<void>(*this);
        }
    public:
        inline constexpr const bool GetIsCompleted() const noexcept
        {
            return Elysium::Core::Template::Threading::Tasks::TaskStatus::RanToCompletion == _Promise._Status;
        }

        inline Elysium::Core::Template::System::uint16_t GetErrorCode() const noexcept
        {
            return _Promise._ErrorCode;
        }
    public:
        inline Task& Wait()
        {
            const bool WaitResult = _Promise._CoroutineCompletionEvent.WaitOne();
            if (!WaitResult)
            {
                bool sdf = false;
            }

            return *this;
        }
    private:
        PromiseType& _Promise;
        CoroutineHandleType _CoroutineFrameHandle;
    };
}
#endif
#endif
