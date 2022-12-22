/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_WATCHERCHANGETYPES
#define ELYSIUM_CORE_IO_WATCHERCHANGETYPES

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

namespace Elysium::Core::IO
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class WatcherChangeTypes : Elysium::Core::uint8_t
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
		return static_cast<WatcherChangeTypes>(static_cast<uint8_t>(Left) | static_cast<uint8_t>(Right));
	}

	inline WatcherChangeTypes operator&(const WatcherChangeTypes Left, const WatcherChangeTypes Right)
	{
		return static_cast<WatcherChangeTypes>(static_cast<uint8_t>(Left) & static_cast<uint8_t>(Right));
	}

	inline WatcherChangeTypes operator|=(const WatcherChangeTypes Left, const WatcherChangeTypes Right)
	{
		return static_cast<WatcherChangeTypes>(static_cast<uint8_t>(Left) | static_cast<uint8_t>(Right));
	}

	inline WatcherChangeTypes operator&=(const WatcherChangeTypes Left, const WatcherChangeTypes Right)
	{
		return static_cast<WatcherChangeTypes>(static_cast<uint8_t>(Left) & static_cast<uint8_t>(Right));
	}
}
#endif

