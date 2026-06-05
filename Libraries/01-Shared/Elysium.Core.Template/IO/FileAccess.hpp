/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_FILEACCESS
#define ELYSIUM_CORE_TEMPLATE_IO_FILEACCESS

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
	enum class FileAccess
		: Elysium::Core::Template::System::uint8_t
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
		return static_cast<FileAccess>(static_cast<Elysium::Core::Template::System::uint8_t>(Left) | static_cast<Elysium::Core::Template::System::uint8_t>(Right));
	}

	inline FileAccess operator&(const FileAccess Left, const FileAccess Right)
	{
		return static_cast<FileAccess>(static_cast<Elysium::Core::Template::System::uint8_t>(Left) & static_cast<Elysium::Core::Template::System::uint8_t>(Right));
	}
}
#endif
