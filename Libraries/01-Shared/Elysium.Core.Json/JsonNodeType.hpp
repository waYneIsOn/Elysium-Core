/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_JSON_JSONNODETYPE
#define ELYSIUM_CORE_JSON_JSONNODETYPE

#ifndef _STDINT
#include <stdint.h>
#endif

namespace Elysium::Core::Json
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class JsonNodeType : uint32_t
#elif defined(__ANDROID__)
	enum class JsonNodeType
#else
#error "undefined os"
#endif
	{
		Document = 0,
		String = 1,
		Integer = 2,
		Float = 3,
		Double = 4,
		Object = 5,
		Array = 6,
		Boolean = 7,
		Null = 8
	};
}
#endif
