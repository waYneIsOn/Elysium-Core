/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_INTERLOCKED_WINDOWS
#define ELYSIUM_CORE_TEMPLATE_THREADING_INTERLOCKED_WINDOWS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../System/Primitives.hpp"
#endif

#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

namespace Elysium::Core::Template::Threading
{
	/// <summary>
	/// Provides atomic operations for variables that are shared by multiple threads.
	/// </summary>
	class Interlocked final
	{
	public:
		Interlocked() = delete;

		Interlocked(const Interlocked& Source) = delete;

		Interlocked(Interlocked&& Right) noexcept = delete;

		~Interlocked() = delete;
	public:
		Interlocked& operator=(const Interlocked& Source) = delete;

		Interlocked& operator=(Interlocked&& Right) noexcept = delete;
	public:
		inline static System::int32_t Add(volatile System::int32_t* Value, const System::int32_t IncrementBy)
		{
			return InterlockedAdd(reinterpret_cast<volatile long*>(Value), IncrementBy);
		}

		inline static System::int64_t Add(volatile System::int64_t* Value, const System::int64_t IncrementBy)
		{
			return InterlockedAdd64(Value, IncrementBy);
		}

		inline static System::int32_t Decrement(volatile System::int32_t* Value)
		{
			return InterlockedDecrement(reinterpret_cast<volatile long*>(Value));
		}

		inline static System::int64_t Decrement(volatile System::int64_t* Value)
		{
			return InterlockedDecrement64(Value);
		}

		inline static System::int32_t Increment(volatile System::int32_t* Value)
		{
			return InterlockedIncrement(reinterpret_cast<volatile long*>(Value));
		}

		inline static System::int64_t Increment(volatile System::int64_t* Value)
		{
			return InterlockedIncrement64(Value);
		}
	};
}
#endif
#endif
