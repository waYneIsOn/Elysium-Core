/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_DATA_ISOLATIONLEVEL
#define ELYSIUM_CORE_DATA_ISOLATIONLEVEL

namespace Elysium
{
	namespace Core
	{
		namespace Data
		{
			enum class IsolationLevel : long
			{
				// ...
				Unspecified = -1,

				// ...
				Chaos = 16,

				// The values in a record being accessed can change at any time.
				ReadUncommitted = 256,

				// The values in a record do not change from the time the record is read until it is rewritten or passed over.
				ReadCommitted = 4096,

				// The relationship between values in different records doesn't change while the transaction is executing.
				RepeatableRead = 65536,

				// The existence of reference records does not change while the transaction is executing. 
				Serializable = 1048576,

				// ...
				Snapshot = 16777216
			};
		}
	}
}
#endif
