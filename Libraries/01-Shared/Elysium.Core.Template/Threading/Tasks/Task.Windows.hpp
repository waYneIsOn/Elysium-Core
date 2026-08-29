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

#ifndef ELYSIUM_CORE_TEMPLATE_COROUTINES_SUSPENDALWAYS
#include "../../Coroutines/SuspendAlways.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_COROUTINES_SUSPENDNEVER
#include "../../Coroutines/SuspendNever.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
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



    template<class Promise>
    struct GetPromise
    {
        Promise* _Promise{};

        bool await_ready() const noexcept
        {
            return false;
        }

        bool await_suspend(Elysium::Core::Template::Coroutines::CoroutineHandle<Promise> Handle) noexcept
        {
            _Promise = &static_cast<Promise&>(Handle);

            // immediately continue the coroutine
            return false;
        }

        Promise& await_resume() const noexcept
        {
            return *_Promise;
        }
    };

    struct SuspendIo
    {
        bool await_ready() const noexcept
        {
            return false;
        }

        void await_suspend(Elysium::Core::Template::Coroutines::CoroutineHandle<>)
        {
            // nothing to do here, IOCP callback will resume the coroutine.
        }

        void await_resume() const noexcept
        { }
    };






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
            Task get_return_object()
            {
                _Handle = Elysium::Core::Template::Coroutines::CoroutineHandle<promise_type>::FromPromise(*this);
                return Task<Result>(_Handle);
            }

            Elysium::Core::Template::Coroutines::SuspendNever initial_suspend()
            {
                return {};
            }

            Elysium::Core::Template::Coroutines::SuspendAlways final_suspend() noexcept
            {
                return {};
            }

            void return_value(Result Value)
            {
                _Result = Value;
            }

            void unhandled_exception()
            {
                //_Exception = std::current_exception();
                bool sdfsdf = false;
            }
        private:
            OVERLAPPED _Overlapped{};
            Elysium::Core::Template::Coroutines::CoroutineHandle<promise_type> _Handle{};

            bool _HasCompletedSynchronously{};
            DWORD _ErrorCode{};

            Result _Result{};
        };
    public:
        using PromiseType = promise_type;
        using CoroutineFrame = Elysium::Core::Template::Coroutines::CoroutineHandle<PromiseType>;
    public:
        constexpr Task() noexcept = delete;
    private:
        inline explicit constexpr Task(CoroutineFrame Handle) noexcept
            : _Handle(Handle)
        { }
    public:
        constexpr Task(const Task& Source) noexcept = delete;

        constexpr Task(Task&& Right) noexcept = delete;

        inline ~Task() noexcept
        {
            _Handle.destroy();
        }
    public:
        constexpr Task& operator=(const Task& Source) noexcept = delete;

        constexpr Task& operator=(Task&& Right) noexcept = delete;
    public:
        inline Result GetResult()
        {
            return static_cast<PromiseType>(_Handle)._Result;
            //return _Handle.ToPromise()._Result;
        }
    private:
        CoroutineFrame _Handle{};
    };
}
#endif
#endif
