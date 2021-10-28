/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SYSTEMSPECIFIC
#define ELYSIUM_CORE_SYSTEMSPECIFIC

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

namespace Elysium::Core
{
	class SystemSpecific
	{
	public:
		SystemSpecific() = delete;
		SystemSpecific(const SystemSpecific& Source) = delete;
		SystemSpecific(SystemSpecific&& Right) noexcept = delete;
		~SystemSpecific() = delete;

		SystemSpecific& operator=(const SystemSpecific& Source) = delete;
		SystemSpecific& operator=(SystemSpecific&& Right) noexcept = delete;
	public:
		static const Elysium::Core::int32_t GetLastErrorCode();
	};
}
#endif
