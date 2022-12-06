/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IASYNCRESULT
#define ELYSIUM_CORE_IASYNCRESULT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_WAITHANDLE
#include "../Elysium.Core.Threading/WaitHandle.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API IAsyncResult
	{
	protected:
		IAsyncResult();
	public:
		IAsyncResult(const IAsyncResult& Source) = delete;

		IAsyncResult(IAsyncResult&& Right) noexcept = delete;

		virtual ~IAsyncResult();
	public:
		IAsyncResult& operator=(const IAsyncResult& Source) = delete;

		IAsyncResult& operator=(IAsyncResult&& Right) noexcept = delete;
	public:
		virtual const void* GetAsyncState() const = 0;

		virtual Elysium::Core::Threading::WaitHandle& GetAsyncWaitHandle() = 0;

		virtual const bool GetCompletedSynchronously() const = 0;

		virtual const bool GetIsCompleted() const = 0;
	};
}
#endif
