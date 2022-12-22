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
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../Elysium.Core.Template/OperatingSystem.hpp"
#endif

namespace Elysium::Core::IO
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class SeekOrigin : Elysium::Core::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
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
