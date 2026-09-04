/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_FILESYSTEM_WATCHERCHANGETYPES
#define ELYSIUM_CORE_TEMPLATE_IO_FILESYSTEM_WATCHERCHANGETYPES

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::FileSystem
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class WatcherChangeTypes
		: Elysium::Core::Template::System::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class WatcherChangeTypes
#else
#error "undefined os"
#endif
	{
		Created = 1,

		Deleted = 2,

		Changed = 4,

		Renamed = 8,

		All = Created | Deleted | Changed | Renamed
	};

	inline WatcherChangeTypes operator|(const WatcherChangeTypes Left, const WatcherChangeTypes Right)
	{
		return static_cast<WatcherChangeTypes>(static_cast<Elysium::Core::Template::System::uint8_t>(Left) | static_cast<Elysium::Core::Template::System::uint8_t>(Right));
	}

	inline WatcherChangeTypes operator&(const WatcherChangeTypes Left, const WatcherChangeTypes Right)
	{
		return static_cast<WatcherChangeTypes>(static_cast<Elysium::Core::Template::System::uint8_t>(Left) & static_cast<Elysium::Core::Template::System::uint8_t>(Right));
	}

	inline WatcherChangeTypes operator|=(const WatcherChangeTypes Left, const WatcherChangeTypes Right)
	{
		return static_cast<WatcherChangeTypes>(static_cast<Elysium::Core::Template::System::uint8_t>(Left) | static_cast<Elysium::Core::Template::System::uint8_t>(Right));
	}

	inline WatcherChangeTypes operator&=(const WatcherChangeTypes Left, const WatcherChangeTypes Right)
	{
		return static_cast<WatcherChangeTypes>(static_cast<Elysium::Core::Template::System::uint8_t>(Left) & static_cast<Elysium::Core::Template::System::uint8_t>(Right));
	}
}
#endif
