/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_DATA_CONNECTIONSTATE
#define ELYSIUM_CORE_DATA_CONNECTIONSTATE

#ifndef _STDINT
#include <stdint.h>
#endif

namespace Elysium::Core::Data
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class ConnectionState : uint32_t
#elif defined(__ANDROID__)
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
		return static_cast<ConnectionState>(static_cast<int>(lhs) | static_cast<int>(rhs));
	}
	inline ConnectionState operator&(ConnectionState lhs, ConnectionState rhs)
	{
		return static_cast<ConnectionState>(static_cast<int>(lhs) & static_cast<int>(rhs));
	}
}
#endif
