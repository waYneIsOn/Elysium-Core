/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_SEEKORIGIN
#define ELYSIUM_CORE_IO_SEEKORIGIN

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::IO
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class SeekOrigin : uint32_t
#elif defined(__ANDROID__)
	enum class SeekOrigin
#else
#error "undefined os"
#endif
	{
		Begin = 0,
		Current = 1,
		End = 2
	};
}
#endif
