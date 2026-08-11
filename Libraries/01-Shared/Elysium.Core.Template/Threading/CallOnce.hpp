/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_CALLONCE
#define ELYSIUM_CORE_TEMPLATE_THREADING_CALLONCE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../Primitives.hpp"
#endif

#ifdef ELYSIUM_CORE_OS_WINDOWS
	#ifndef _SYNCHAPI_H_
	#include <synchapi.h>
	#endif
#else
#error "unsupported os"
#endif

namespace Elysium::Core::Template::Threading
{
	class CallOnce
	{
	public:
		constexpr CallOnce() noexcept = default;

		constexpr CallOnce(const CallOnce& Source) = delete;

		constexpr CallOnce(CallOnce&& Right) noexcept = delete;

		constexpr ~CallOnce() noexcept = default;
	public:
		constexpr CallOnce& operator=(const CallOnce& Source) = delete;

		constexpr CallOnce& operator=(CallOnce&& Right) noexcept = delete;
	public:
		template <class Callable, class... Args>
		inline constexpr void operator()(Callable&& Function, Args&&... Parameters)
		{
			// @ToDo: STL uses noexcept.
#ifdef ELYSIUM_CORE_OS_WINDOWS
			Elysium::Core::Template::System::int32_t Pending;
			if (!InitOnceBeginInitialize(&_NativeObject, 0, &Pending, nullptr))
			{
				abort();
			}

			if (0 != Pending)
			{
				// @ToDo: STL uses RAII object _Init_once_completer. need to have a look whether this is better! 
				try
				{
					Function(Parameters...);	// @ToDo: STL uses std::invoke - really need to have a look at it
					InitOnceComplete(&_NativeObject, 0, nullptr);
				}
				catch (...)
				{
					InitOnceComplete(&_NativeObject, 0x00000004UL /*INIT_ONCE_INIT_FAILED*/, nullptr);
					throw;
				}
			}
#else
#error "unsupported os"
#endif
		}
	private:
#ifdef ELYSIUM_CORE_OS_WINDOWS
		INIT_ONCE _NativeObject = INIT_ONCE_STATIC_INIT;
#elif defined ELYSIUM_CORE_OS_LINUX
		//pthread_once _NativeObject;
#else
#error "unsupported os"
#endif
	};
}
#endif
