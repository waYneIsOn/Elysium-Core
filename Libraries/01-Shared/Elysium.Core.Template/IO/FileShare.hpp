/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_FILESHARE
#define ELYSIUM_CORE_TEMPLATE_IO_FILESHARE

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
	enum class FileShare
		: Elysium::Core::Template::System::uint32_t
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
