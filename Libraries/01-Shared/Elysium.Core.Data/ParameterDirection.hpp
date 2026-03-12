/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATA_PARAMETERDIRECTION
#define ELYSIUM_CORE_DATA_PARAMETERDIRECTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../Elysium.Core.Template/System/OperatingSystem.hpp"
#endif

namespace Elysium::Core::Data
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class ParameterDirection
		: Elysium::Core::int32_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class ParameterDirection
#else
#error "undefined os"
#endif
	{
		Input = 1,

		Output = 2,

		InputOutput = 3,

		ReturnValue = 6,
	};
}
#endif
