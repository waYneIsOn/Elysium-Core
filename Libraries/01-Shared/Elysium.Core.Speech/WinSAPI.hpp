/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SPEECH_INTERNAL_WINSAPI
#define ELYSIUM_CORE_SPEECH_INTERNAL_WINSAPI

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
namespace Elysium::Core::Speech::Internal
{
	class WinSAPI final
	{
	public:
		WinSAPI() = delete;

		WinSAPI(const WinSAPI& Source) = delete;

		WinSAPI(WinSAPI&& Right) noexcept = delete;

		~WinSAPI() = delete;
	public:
		WinSAPI& operator=(const WinSAPI& Source) = delete;

		WinSAPI& operator=(WinSAPI&& Right) noexcept = delete;
	public:
		static void Initialize();

		static void Shutdown();
	};
}
#endif
#endif
