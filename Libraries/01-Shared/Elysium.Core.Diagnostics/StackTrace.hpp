/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DIAGNOSTICS_STACKTRACE
#define ELYSIUM_CORE_DIAGNOSTICS_STACKTRACE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_DIAGNOSTICS_STACKFRAME
#include "StackFrame.hpp"
#endif

namespace Elysium::Core::Diagnostics
{
	class ELYSIUM_CORE_API StackTrace final
	{
	public:
		StackTrace();

		StackTrace(const StackTrace& Source) = delete;

		StackTrace(StackTrace&& Right) noexcept = delete;

		~StackTrace();
	public:
		StackTrace& operator=(const StackTrace& Source) = delete;

		StackTrace& operator=(StackTrace&& Right) noexcept = delete;
	public:
		const Elysium::Core::size GetFrameCount() const;
	private:
		Elysium::Core::size _FrameCount;
	};
}
#endif
