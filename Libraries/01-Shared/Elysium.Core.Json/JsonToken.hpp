/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_JSON_JSONTOKEN
#define ELYSIUM_CORE_JSON_JSONTOKEN

#ifndef _STDINT
#include <stdint.h>
#endif

namespace Elysium::Core::Json
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class JsonToken : uint32_t
#elif defined(__ANDROID__)
	enum class JsonToken
#else
#error "undefined os"
#endif
	{
		None = 0,

		StartedObject = 1,
		EndedObject = 2,

		StartedArray = 3,
		EndedArray = 4,

		PropertyName = 5,

		Integer = 6,
		Float = 7,
		String = 8,
		Boolean = 9,
		Null = 11,
	};
}
#endif
