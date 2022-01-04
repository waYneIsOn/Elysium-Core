/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_EVENTARGS
#define ELYSIUM_CORE_EVENTARGS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API EventArgs
	{
	public:
		EventArgs();

		EventArgs(const EventArgs& Source) = delete;

		EventArgs(EventArgs&& Right) noexcept = delete;

		virtual ~EventArgs();
	public:
		EventArgs& operator=(const EventArgs& Source) = delete;

		EventArgs& operator=(EventArgs&& Right) noexcept = delete;
	};
}
#endif
