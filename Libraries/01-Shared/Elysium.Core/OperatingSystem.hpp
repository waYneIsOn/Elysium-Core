/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_OPERATINGSYSTEM
#define ELYSIUM_CORE_OPERATINGSYSTEM

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_PLATFORMID
#include "PlatformID.hpp"
#endif

#ifndef ELYSIUM_CORE_VERSION
#include "Version.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API OperatingSystem final
	{
	public:
		OperatingSystem(const PlatformID& PlatformID, const Version& Version) noexcept;

		OperatingSystem(const OperatingSystem& Source) noexcept;

		OperatingSystem(OperatingSystem&& Right) noexcept;

		~OperatingSystem() noexcept;
	public:
		OperatingSystem& operator=(const OperatingSystem& Source) noexcept;

		OperatingSystem& operator=(OperatingSystem&& Right) noexcept;
	public:
		const PlatformID GetPlatform() const;

		const Version& GetVersion() const;
	public:
		const bool IsWindows() const;
	private:
		PlatformID _PlatformId;
		Version _Version;
	};
}
#endif
