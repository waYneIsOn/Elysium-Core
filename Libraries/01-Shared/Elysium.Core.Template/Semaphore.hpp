/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_SEMAPHORE
#define ELYSIUM_CORE_TEMPLATE_THREADING_SEMAPHORE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_WAITHANDLE
#include "WaitHandle.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_SEMAPHOREFULLEXCEPTION
// ToDo
#include "../Elysium.Core.Threading/SemaphoreFullException.hpp"
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
	/// Limits the number of threads that can access a resource or pool of resources concurrently.
	/// </summary>
	class Semaphore final : public WaitHandle
	{
	public:
		Semaphore(const System::uint32_t InitialCount, const System::uint32_t MaximumCount, const char8_t* Name = nullptr);

		//Semaphore(const uint32_t InitialCount, const uint32_t MaximumCount, const String& Name, bool& CreatedNew);

		Semaphore(const Semaphore& Source) = delete;

		Semaphore(Semaphore&& Right) noexcept = delete;

		virtual ~Semaphore();
	public:
		Semaphore& operator=(const Semaphore& Source) = delete;

		Semaphore& operator=(Semaphore&& Right) noexcept = delete;
	public:
		const System::uint32_t Release();
	};

	inline Elysium::Core::Template::Threading::Semaphore::Semaphore(const System::uint32_t InitialCount, const System::uint32_t MaximumCount, const char8_t* Name)
		: WaitHandle(CreateSemaphoreW(nullptr, InitialCount, MaximumCount, nullptr))
	{ }

	inline Elysium::Core::Template::Threading::Semaphore::~Semaphore()
	{ }

	inline const System::uint32_t Elysium::Core::Template::Threading::Semaphore::Release()
	{
		long PreviousCount;
		bool Result = ReleaseSemaphore(_Handle, 1, &PreviousCount);
		if (Result)
		{
			return static_cast<System::uint32_t>(PreviousCount);
		}
		else
		{
			throw Elysium::Core::Threading::SemaphoreFullException();
		}
	}
}
#endif
