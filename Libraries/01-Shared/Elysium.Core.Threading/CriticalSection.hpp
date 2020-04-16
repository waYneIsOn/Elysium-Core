/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_THREADING_CRITICALSECTION
#define ELYSIUM_CORE_THREADING_CRITICALSECTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_SYSTEM
#include "System.hpp"
#endif

namespace Elysium::Core::Threading
{
	class ELYSIUM_CORE_API CriticalSection final
	{
	public:
		CriticalSection();
		CriticalSection(const CriticalSection& Source) = delete;
		CriticalSection(CriticalSection&& Right) noexcept = delete;
		~CriticalSection();

		CriticalSection& operator=(const CriticalSection& Source) = delete;
		CriticalSection& operator=(CriticalSection&& Right) noexcept = delete;

		const bool Enter(const bool Blocking = true);
		void Exit();
	private:
		ELYSIUM_CRITICAL_SECTION_HANDLE _Handle;
	};
}
#endif
