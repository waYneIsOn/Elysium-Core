/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_THREADING_THREADPRIORITY
#define ELYSIUM_CORE_THREADING_THREADPRIORITY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Threading
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class ThreadPriority : uint32_t
#elif defined(__ANDROID__)
	enum class ThreadPriority
#else
#error "undefined os"
#endif
	{
		Lowest = 0,
		BelowNormal = 1,
		Normal = 2,
		AboveNormal = 3,
		Highest = 4
	};
}
#endif