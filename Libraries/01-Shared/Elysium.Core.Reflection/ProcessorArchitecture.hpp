/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_REFLECTION_PROCESSORARCHITECTURE
#define ELYSIUM_CORE_REFLECTION_PROCESSORARCHITECTURE

#ifndef _STDINT
#include <stdint.h>
#endif

namespace Elysium::Core::Reflection
{
	// https://en.wikipedia.org/wiki/Comparison_of_instruction_set_architectures
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class ProcessorArchitecture : uint32_t
#elif defined(__ANDROID__)
	enum class ProcessorArchitecture
#else
#error "undefined os"
#endif
	{
		None = 0,
		MSIL = 1,
		x86 = 2,
		IA64 = 3,
		Amd64 = 4,
		ARM32 = 5,
		ARM64 = 6,
	};
}
#endif
