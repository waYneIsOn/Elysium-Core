/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_FILEACCESS
#define ELYSIUM_CORE_IO_FILEACCESS

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
	enum class FileAccess : Elysium::Core::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class FileAccess
#else
#error "undefined os"
#endif
	{
		Read = 1,

		Write = 2
	};

	inline FileAccess operator|(const FileAccess Left, const FileAccess Right)
	{
		return static_cast<FileAccess>(static_cast<Elysium::Core::uint8_t>(Left) | static_cast<Elysium::Core::uint8_t>(Right));
	}

	inline FileAccess operator&(const FileAccess Left, const FileAccess Right)
	{
		return static_cast<FileAccess>(static_cast<Elysium::Core::uint8_t>(Left) & static_cast<Elysium::Core::uint8_t>(Right));
	}
}
#endif
