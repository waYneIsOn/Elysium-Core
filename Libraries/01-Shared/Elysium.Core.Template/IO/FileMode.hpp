/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_FILEMODE
#define ELYSIUM_CORE_TEMPLATE_IO_FILEMODE

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
	enum class FileMode 
		: Elysium::Core::Template::System::uint32_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class FileMode
#else
#error "undefined os"
#endif
	{
		CreateNew = 1,

		Create = 2,

		Open = 3,

		OpenOrCreate = 4,

		Truncate = 5,

		Append = 6
	};
}
#endif
