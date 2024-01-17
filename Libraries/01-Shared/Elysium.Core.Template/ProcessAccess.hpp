/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_PROCESSACCESS
#define ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_PROCESSACCESS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../Elysium.Core.Template/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../Elysium.Core.Template/OperatingSystem.hpp"
#endif

namespace Elysium::Core::Template::Diagnostics
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class ProcessAccess : Elysium::Core::Template::System::uint32_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class ProcessAccess
#else
#error "undefined os"
#endif
	{
		Terminate = 0x0001,

		CreateThread = 0x0002,

		SetSessionId = 0x0004,

		VMOperation = 0x0008,

		VMRead = 0x0010,

		VMWrite = 0x0020,

		DuplicateHandle = 0x0040,

		Create = 0x0080,

		SetQuota = 0x0100,

		SetInformation = 0x0200,

		QueryInformation = 0x0400,

		QueryLimitedInformation = 0x1000,

		StandardRightsRequired = 0x000F0000,

		Synchronize = 0x00100000,

		ReadControl = 0x00020000,

		AllAccess = StandardRightsRequired | Synchronize | 0xFFF
	};

	inline ProcessAccess operator|(const ProcessAccess Left, const ProcessAccess Right)
	{
		return static_cast<ProcessAccess>(static_cast<Elysium::Core::Template::System::uint32_t>(Left) | static_cast<Elysium::Core::Template::System::uint32_t>(Right));
	}

	inline ProcessAccess operator&(const ProcessAccess Left, const ProcessAccess Right)
	{
		return static_cast<ProcessAccess>(static_cast<Elysium::Core::Template::System::uint32_t>(Left) & static_cast<Elysium::Core::Template::System::uint32_t>(Right));
	}
}
#endif
