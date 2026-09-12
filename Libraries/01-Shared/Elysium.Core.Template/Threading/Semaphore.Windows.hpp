/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_SEMAPHORE_WINDOWS
#define ELYSIUM_CORE_TEMPLATE_THREADING_SEMAPHORE_WINDOWS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_WAITHANDLE
#include "WaitHandle.hpp"
#endif

#ifndef _WINDOWS_
#define _WINSOCKAPI_ // don't include winsock
#include <Windows.h>
#endif

namespace Elysium::Core::Template::Threading
{
	/// <summary>
	/// Limits the number of threads that can access a resource or pool of resources concurrently.
	/// </summary>
	class Semaphore final 
		: public WaitHandle
	{
	public:
		Semaphore() = delete;

		inline Semaphore(const Elysium::Core::Template::System::uint32_t InitialCount, const Elysium::Core::Template::System::uint32_t MaximumCount, const char8_t* Name = nullptr)
			: WaitHandle(CreateSemaphoreW(nullptr, InitialCount, MaximumCount, nullptr))
		{ }

		//inline Semaphore(const Elysium::Core::Template::System::uint32_t InitialCount, const Elysium::Core::Template::System::uint32_t MaximumCount, const String& Name, bool& CreatedNew);

		Semaphore(const Semaphore& Source) = delete;

		Semaphore(Semaphore&& Right) noexcept = delete;

		virtual ~Semaphore() = default;
	public:
		Semaphore& operator=(const Semaphore& Source) = delete;

		Semaphore& operator=(Semaphore&& Right) noexcept = delete;
	public:
		inline const Elysium::Core::Template::System::uint32_t Release()
		{
			long PreviousCount;
			bool Result = ReleaseSemaphore(_Handle, 1, &PreviousCount);
			if (Result)
			{
				return static_cast<System::uint32_t>(PreviousCount);
			}
			else
			{	// @ToDo: throw Elysium::Core::Template::Threading::SemaphoreFullException();
				throw 1;
			}
		}
	};
}
#endif
#endif
