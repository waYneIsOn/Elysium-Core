/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_SEEKORIGIN
#define ELYSIUM_CORE_TEMPLATE_IO_SEEKORIGIN

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class SeekOrigin
		: Elysium::Core::Template::System::uint8_t
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
