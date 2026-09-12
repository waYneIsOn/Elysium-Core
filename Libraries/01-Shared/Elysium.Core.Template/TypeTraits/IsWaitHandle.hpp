/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISWAITHANDLE
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISWAITHANDLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_REMOVECONSTVOLATILE
#include "../Functional/RemoveConstVolatile.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_AUTORESETEVENT
#include "../Threading/AutoResetEvent.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_EVENTWAITHANDLE
#include "../Threading/EventWaitHandle.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_MANUALRESETEVENT
#include "../Threading/ManualResetEvent.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_MUTEX
#include "../Threading/Mutex.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_SEMAPHORE
#include "../Threading/Semaphore.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_INTEGRALCONSTANT
#include "IntegralConstant.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISANYOF
#include "IsAnyOf.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
	template <class T>
	inline constexpr bool IsWaitHandleValue = IsAnyOfValue<Functional::RemoveConstVolatileType<T>,
		Elysium::Core::Template::Threading::AutoResetEvent,
		Elysium::Core::Template::Threading::EventWaitHandle,
		Elysium::Core::Template::Threading::ManualResetEvent,
		Elysium::Core::Template::Threading::Mutex, 
		Elysium::Core::Template::Threading::Semaphore
	>;

	template <class T>
	struct IsWaitHandle : public IntegralConstant<bool, IsWaitHandleValue<T>>
	{ };
}
#endif