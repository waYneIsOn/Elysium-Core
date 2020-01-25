/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_THREADING_INTERLOCKED
#define ELYSIUM_CORE_THREADING_INTERLOCKED

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Threading
{
	// Provides atomic operations for variables that are shared by multiple threads.
	class ELYSIUM_CORE_API Interlocked final
	{
	public:
		static int32_t Add(int32_t& Location, int32_t Value);
		static int64_t Add(int64_t& Location, int64_t Value);
		
		static int32_t Decrement(int32_t& Location);
		static int64_t Decrement(int64_t& Location);

		static int32_t Increment(int32_t& Location);
		static int64_t Increment(int64_t& Location);
	private:
		Interlocked();
		~Interlocked();
	};
}
#endif
