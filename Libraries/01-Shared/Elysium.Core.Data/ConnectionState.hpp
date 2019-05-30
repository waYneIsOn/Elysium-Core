/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_DATA_CONNECTIONSTATE
#define ELYSIUM_CORE_DATA_CONNECTIONSTATE

namespace Elysium
{
	namespace Core
	{
		namespace Data
		{
			enum class ConnectionState : int
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
	}
}
#endif
