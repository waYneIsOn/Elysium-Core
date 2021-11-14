/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATA_ISOLATIONLEVEL
#define ELYSIUM_CORE_DATA_ISOLATIONLEVEL

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
	enum class IsolationLevel : Elysium::Core::int32_t
#elif defined ELYSIUM_CORE_OS_ANDROID
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
