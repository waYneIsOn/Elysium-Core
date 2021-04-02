/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DIAGNOSTICS_PROCESS
#define ELYSIUM_CORE_DIAGNOSTICS_PROCESS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

namespace Elysium::Core::Diagnostics
{
	class ELYSIUM_CORE_API Process final
	{
	public:
		Process();
		Process(const Process& Source) = delete;
		Process(Process&& Right) noexcept = delete;
		~Process();

		Process& operator=(const Process& Source) = delete;
		Process& operator=(Process&& Right) noexcept = delete;
	private:

	};
}
#endif
