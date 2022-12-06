/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_INTERLOCKED
#define ELYSIUM_CORE_TEMPLATE_THREADING_INTERLOCKED

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
	#ifndef _WINDOWS_
	#define _WINSOCKAPI_ // don't include winsock
	#include <Windows.h>
	#endif
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
		static System::int32_t Add(volatile System::int32_t* Value, const System::int32_t IncrementBy);

		static System::int64_t Add(volatile System::int64_t* Value, const System::int64_t IncrementBy);

		static System::int32_t Decrement(volatile System::int32_t* Value);

		static System::int64_t Decrement(volatile System::int64_t* Value);

		static System::int32_t Increment(volatile System::int32_t* Value);

		static System::int64_t Increment(volatile System::int64_t* Value);
	};

	inline System::int32_t Elysium::Core::Template::Threading::Interlocked::Add(volatile System::int32_t* Value, const System::int32_t IncrementBy)
	{
		return InterlockedAdd(reinterpret_cast<volatile long*>(Value), IncrementBy);
	}

	inline System::int64_t Elysium::Core::Template::Threading::Interlocked::Add(volatile System::int64_t* Value, const System::int64_t IncrementBy)
	{
		return InterlockedAdd64(Value, IncrementBy);
	}

	inline System::int32_t Interlocked::Decrement(volatile System::int32_t* Value)
	{
		return InterlockedDecrement(reinterpret_cast<volatile long*>(Value));
	}

	inline System::int64_t Interlocked::Decrement(volatile System::int64_t* Value)
	{
		return InterlockedDecrement64(Value);
	}

	inline System::int32_t Interlocked::Increment(volatile System::int32_t* Value)
	{
		return InterlockedIncrement(reinterpret_cast<volatile long*>(Value));
	}

	inline System::int64_t Interlocked::Increment(volatile System::int64_t* Value)
	{
		return InterlockedIncrement64(Value);
	}
}
#endif
