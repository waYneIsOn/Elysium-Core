/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_COROUTINES_PROMISES_PROMISEEXAMPLE
#define ELYSIUM_CORE_TEMPLATE_COROUTINES_PROMISES_PROMISEEXAMPLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_COROUTINES_AWAITER_SUSPENDALWAYS
#include "../Awaiter/SuspendAlways.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_COROUTINES_AWAITER_SUSPENDNEVER
#include "../Awaiter/SuspendNever.hpp"
#endif

#ifndef _FUTURE_
#include <future>
#endif

namespace Elysium::Core::Template::Coroutines::Promises
{
    template <class T>
	struct _PromiseExample
	{
        /// <summary>
        /// 1.) After the compiler has created the coroutine frame, promise_type etc., it calls this method to construct the "wrapping object".
        /// </summary>
        /// <returns></returns>
        inline std::future<T> get_return_object()
        {
            return {};
        }

        /// <summary>
        /// 2.) Afterwards the compiler calls this method querying for an Awaiter to be used in suspending the coroutine or running it's body right away.
        /// </summary>
        /// <returns></returns>
        inline Elysium::Core::Template::Coroutines::Awaiter::SuspendNever initial_suspend()
        {
            return {};
        }

        /// <summary>
        /// 3.) If any exception occurres during the execution of the coroutine's body, this method gets called by the compiler.
        /// </summary>
        inline void unhandled_exception()
        {
            /*
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
            */
        }

        /// <summary>
        /// 4.) When co_return is called, the compiler calls this method to set the result.
        /// </summary>
        /// <param name="Value"></param>
        inline void return_value(T Value)
        { }

        /// <summary>
        /// 4.) Eventually the compiler calls this method to give one last suspension point before the coroutine-frame gets destroyed.
        /// </summary>
        /// <returns></returns>
        inline Elysium::Core::Template::Coroutines::Awaiter::SuspendAlways final_suspend() noexcept
        {
            return {};
        }

        /*
        void yield_value(Result Value)
        { }
        */
	};

    template <>
    struct _PromiseExample<void>
    {
        inline std::future<void> get_return_object()
        {
            return {};
        }

        inline Elysium::Core::Template::Coroutines::Awaiter::SuspendNever initial_suspend()
        {
            return {};
        }

        inline void unhandled_exception()
        {
            /*
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
            */
        }

        inline void return_void()
        { }

        inline Elysium::Core::Template::Coroutines::Awaiter::SuspendAlways final_suspend() noexcept
        {
            return {};
        }
        /*
        void yield_value(Result Value)
        { }
        */
    };
}
#endif
