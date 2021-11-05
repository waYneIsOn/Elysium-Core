/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_INTERNAL_WRAPPEDOVERLAP
#define ELYSIUM_CORE_INTERNAL_WRAPPEDOVERLAP

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_IASYNCRESULT
#include "IAsyncResult.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "System.hpp"
#endif

#ifndef _MINWINBASE_
#include <minwinbase.h>
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
namespace Elysium::Core::Internal
{
	class ELYSIUM_CORE_API WrappedOverlap final
	{
	public:
		WrappedOverlap(const Elysium::Core::size Position, IAsyncResult* AsyncResult);

		WrappedOverlap(const WrappedOverlap& Source) = delete;

		WrappedOverlap(WrappedOverlap&& Right) noexcept = delete;

		~WrappedOverlap();
	public:
		WrappedOverlap& operator=(const WrappedOverlap& Source) = delete;

		WrappedOverlap& operator=(WrappedOverlap&& Right) noexcept = delete;
	public:
		OVERLAPPED _Overlapped;
		IAsyncResult* _AsyncResult;
	};
}
#endif
#endif
