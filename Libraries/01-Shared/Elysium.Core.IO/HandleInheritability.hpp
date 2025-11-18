/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_HANDLEINHERITABILITY
#define ELYSIUM_CORE_IO_HANDLEINHERITABILITY

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
	enum class HandleInheritability 
		: Elysium::Core::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class HandleInheritability
#else
#error "undefined os"
#endif
	{
		None = 0,

		Inheritable = 1
	};
}
#endif
