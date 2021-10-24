/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_SEEKORIGIN
#define ELYSIUM_CORE_IO_SEEKORIGIN

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core.Template/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core.Template/System.hpp"
#endif

namespace Elysium::Core::IO
{
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	enum class SeekOrigin : Elysium::Core::uint32_t
#elif defined(ELYSIUM_CORE_OS_ANDROID)
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
