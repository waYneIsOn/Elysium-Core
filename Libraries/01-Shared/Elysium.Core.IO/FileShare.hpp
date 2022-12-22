/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_FILESHARE
#define ELYSIUM_CORE_IO_FILESHARE

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
	enum class FileShare : Elysium::Core::uint32_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class FileShare
#else
#error "undefined os"
#endif
	{
		None = 0,

		Read = 1,

		Write = 2,

		ReadWrite = 3,

		Delete = 4,

		Inheritable = 16,
	};
}
#endif
