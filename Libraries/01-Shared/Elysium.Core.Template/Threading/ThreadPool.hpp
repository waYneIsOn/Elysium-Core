/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_THREADPOOL
#define ELYSIUM_CORE_TEMPLATE_THREADING_THREADPOOL

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_CALLONCE
#include "CallOnce.hpp"
#endif

namespace Elysium::Core::Template::Threading
{
	class ThreadPool final
	{
	public:
		constexpr ThreadPool() = delete;

		constexpr ThreadPool(const ThreadPool& Source) = delete;

		constexpr ThreadPool(ThreadPool&& Right) noexcept = delete;

		~ThreadPool() = delete;
	public:
		ThreadPool& operator=(const ThreadPool& Source) = delete;

		ThreadPool& operator=(ThreadPool&& Right) noexcept = delete;
	public:

	private:
		//void Submit();
	private:
		//inline static Elysium::Core::Template::Threading::CallOnce _InitializedFlag;
	};
}
#endif
