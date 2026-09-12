/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_CRITICALSECTION_WINDOWS
#define ELYSIUM_CORE_TEMPLATE_THREADING_CRITICALSECTION_WINDOWS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

namespace Elysium::Core::Template::Threading
{
	/// <summary>
	/// 
	/// </summary>
	class CriticalSection final
	{
	public:
		inline constexpr CriticalSection()
			: _Handle()
		{
			InitializeCriticalSection(&_Handle);
		}

		CriticalSection(const CriticalSection& Source) = delete;

		CriticalSection(CriticalSection&& Right) noexcept = delete;

		inline constexpr ~CriticalSection()
		{
			DeleteCriticalSection(&_Handle);
		}
	public:
		CriticalSection& operator=(const CriticalSection& Source) = delete;

		CriticalSection& operator=(CriticalSection&& Right) noexcept = delete;
	public:
		inline const bool Enter(const bool Blocking = true) noexcept
		{
			if (TryEnterCriticalSection(&_Handle) == 0)
			{
				if (!Blocking)
				{
					return false;
				}
				EnterCriticalSection(&_Handle);
			}
			return true;
		}

		inline void Exit() noexcept
		{
			LeaveCriticalSection(&_Handle);
		}
	private:
		CRITICAL_SECTION _Handle;
	};
}
#endif
#endif
