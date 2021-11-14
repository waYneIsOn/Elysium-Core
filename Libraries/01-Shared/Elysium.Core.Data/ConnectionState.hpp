/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATA_CONNECTIONSTATE
#define ELYSIUM_CORE_DATA_CONNECTIONSTATE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

namespace Elysium::Core::Data
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class ConnectionState : Elysium::Core::uint32_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class ConnectionState
#else
#error "undefined os"
#endif
	{
		Closed = 0,

		Open = 1,

		Connecting = 2,

		Executing = 4,

		Fetching = 8,

		Broken = 16,
	};

	inline ConnectionState operator|(ConnectionState lhs, ConnectionState rhs)
	{
		return static_cast<ConnectionState>(static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs));
	}
	inline ConnectionState operator&(ConnectionState lhs, ConnectionState rhs)
	{
		return static_cast<ConnectionState>(static_cast<uint32_t>(lhs) & static_cast<uint32_t>(rhs));
	}
}
#endif
