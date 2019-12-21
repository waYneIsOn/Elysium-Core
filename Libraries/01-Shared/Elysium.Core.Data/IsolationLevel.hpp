/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_DATA_ISOLATIONLEVEL
#define ELYSIUM_CORE_DATA_ISOLATIONLEVEL

#ifndef _STDINT
#include <stdint.h>
#endif

namespace Elysium::Core::Data
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class IsolationLevel : int32_t
#elif defined(__ANDROID__)
	enum class IsolationLevel
#else
#error "undefined os"
#endif
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
#endif
