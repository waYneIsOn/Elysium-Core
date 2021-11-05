/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_THREADING_MUTEX
#define ELYSIUM_CORE_THREADING_MUTEX

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_THREADING_WAITHANDLE
#include "WaitHandle.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

namespace Elysium::Core::Threading
{
	// A synchronization primitive that can also be used for interprocess synchronization.
	class ELYSIUM_CORE_API Mutex final : public WaitHandle
	{
	public:
		Mutex();

		Mutex(const bool InitiallyOwned);

		Mutex(const bool InitiallyOwned, const String& Name);

		//Mutex(const bool InitiallyOwned, const String& Name, bool& CreatedNew);

		Mutex(const Mutex& Source) = delete;

		Mutex(Mutex&& Right) noexcept = delete;

		~Mutex();
	public:
		Mutex& operator=(const Mutex& Source) = delete;

		Mutex& operator=(Mutex&& Right) noexcept = delete;
	public:
		void Release();
	};
}
#endif
