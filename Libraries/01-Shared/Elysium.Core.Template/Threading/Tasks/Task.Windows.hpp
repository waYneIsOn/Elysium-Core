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

#ifndef ELYSIUM_CORE_TEMPLATE_COROUTINES_COROUTINEHANDLE
#include "../../Coroutines/CoroutineHandle.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_COROUTINES_AWAITER_SUSPENDALWAYS
#include "../../Coroutines/Awaiter/SuspendAlways.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_COROUTINES_AWAITER_SUSPENDNEVER
#include "../../Coroutines/Awaiter/SuspendNever.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
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

#if defined ELYSIUM_CORE_OS_WINDOWS
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

namespace Elysium::Core::Template::Threading::Tasks
{
    template <class Result>
    class Task
    {
    public:
        friend class Elysium::Core::Template::IO::Device::FileDevice;
    public:
        struct promise_type
        {
        public:
            friend class Task<Result>;
            friend class Elysium::Core::Template::IO::Device::FileDevice;
        public:
            Task<Result> get_return_object()
            {
                _Handle = Elysium::Core::Template::Coroutines::CoroutineHandle<promise_type>::FromPromise(*this);
                return Task<Result>(_Handle);
            }

            Elysium::Core::Template::Coroutines::Awaiter::SuspendNever initial_suspend()
            {
                return {};
            }

            Elysium::Core::Template::Coroutines::Awaiter::SuspendAlways final_suspend() noexcept
            {
                //OutputDebugStringA("FINAL SUSPEND\r\n");

                _Status = Elysium::Core::Template::Threading::Tasks::TaskStatus::RanToCompletion;
                _CoroutineCompletionEvent.Set();

                return { };
            }
            /*
            void return_void()
            { }
            */
            void return_value(Result Value)
            {
                /*
                if (nullptr != _ExceptionPointer)
                {
                    std::rethrow_exception(_ExceptionPointer);
                }
                */
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
            OVERLAPPED _Overlapped{};
            Elysium::Core::Template::Coroutines::CoroutineHandle<promise_type> _Handle{};
            //Elysium::Core::Template::Coroutines::CoroutineHandle<> _OuterCoroutineHandle{};

            Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::Threading::Tasks::TaskStatus> _Status{};

            Elysium::Core::Template::Threading::Atomic<bool> _HasCompletedSynchronously{};
            DWORD _ErrorCode{};
            Result _Result{};

            Elysium::Core::Template::Threading::ManualResetEvent _CoroutineCompletionEvent{};
        };
    public:
        using PromiseType = promise_type;
        using CoroutineFrame = Elysium::Core::Template::Coroutines::CoroutineHandle<PromiseType>;
    public:
        constexpr Task() noexcept = delete;
    private:
        inline explicit constexpr Task(CoroutineFrame CoroutineFrameHandle) noexcept
            : _CoroutineFrameHandle(CoroutineFrameHandle), _Promise(&_CoroutineFrameHandle.ToPromise())
        { }
    public:
        constexpr Task(const Task& Source) noexcept = delete;

        constexpr Task(Task&& Right) noexcept = delete;

        inline ~Task() noexcept
        {
            //Wait();

            //_CoroutineFrameHandle.destroy();
        }
    public:
        constexpr Task& operator=(const Task& Source) noexcept = delete;

        constexpr Task& operator=(Task&& Right) noexcept = delete;
    public:
        inline constexpr const bool GetIsCompleted() const noexcept
        {
            return Elysium::Core::Template::Threading::Tasks::TaskStatus::RanToCompletion == _Promise->_Status;
        }

        inline Elysium::Core::Template::System::uint16_t GetErrorCode()
        {
            return _Promise->_ErrorCode;
        }

        inline Result GetResult()
        {
            return _CoroutineFrameHandle.ToPromise()._Result;
        }
    public:
        inline Task<Result>& Wait()
        {
            _Promise->_CoroutineCompletionEvent.WaitOne();
            //_Promise->_IoCallbackDoneEvent.WaitOne();
            return *this;
        }
    private:
        CoroutineFrame _CoroutineFrameHandle{};

        // temporary?
        PromiseType* _Promise{};
    };
    /*
    template <>
    class Task<void>
    { };
    */
}
#endif
#endif
