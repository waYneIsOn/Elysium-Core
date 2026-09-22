/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_COROUTINES_COROUTINECONTINUATIONSTATE
#define ELYSIUM_CORE_TEMPLATE_COROUTINES_COROUTINECONTINUATIONSTATE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::Coroutines
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class CoroutineContinuationState
		: Elysium::Core::Template::System::uint8_t
#else
	enum class CoroutineContinuationState
#endif
	{
		Pending = 0,

		Waiting = 1,

		Completed = 2
	};
}
#endif
