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

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Data
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class ParameterDirection : int32_t
#elif defined(__ANDROID__)
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
