/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_INTERNAL_WINCNG
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_INTERNAL_WINCNG

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

#ifndef _WINDOWS_
#include <windows.h>
#endif

#ifndef __BCRYPT_H__
#include <bcrypt.h>
#endif

#pragma comment (lib, "bcrypt.lib")

#if defined ELYSIUM_CORE_OS_WINDOWS
namespace Elysium::Core::Security::Cryptography::Internal
{
	class WinCNG final
	{
	public:
		WinCNG() = delete;

		WinCNG(const WinCNG& Source) = delete;

		WinCNG(WinCNG&& Right) noexcept = delete;

		~WinCNG() = delete;
	public:
		WinCNG& operator=(const WinCNG& Source) = delete;

		WinCNG& operator=(WinCNG&& Right) noexcept = delete;
	public:
		static void Test();
	};
}
#endif
#endif
