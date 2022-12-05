/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DIAGNOSTICS_INTERNAL_WINSYMBOLS
#define ELYSIUM_CORE_DIAGNOSTICS_INTERNAL_WINSYMBOLS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../Elysium.Core.Template/OperatingSystem.hpp"
#endif

namespace Elysium::Core::Diagnostics::Internal
{
	class WinSymbols final
	{
	public:
		WinSymbols() = delete;

		WinSymbols(const WinSymbols& Source) = delete;

		WinSymbols(WinSymbols&& Right) noexcept = delete;

		~WinSymbols() noexcept = delete;
	public:
		WinSymbols& operator=(const WinSymbols& Source) = delete;

		WinSymbols& operator=(WinSymbols&& Right) noexcept = delete;
	public:
		static void Initialize();

		static void Shutdown();
	};
}
#endif
