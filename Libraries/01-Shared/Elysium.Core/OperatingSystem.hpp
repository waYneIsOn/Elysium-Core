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
		constexpr OperatingSystem(const PlatformID& PlatformID, const Version& Version) noexcept
			: _PlatformId(PlatformID), _Version(Version)
		{ }

		constexpr OperatingSystem(const OperatingSystem& Source) noexcept
			: _PlatformId(Source._PlatformId), _Version(Source._Version)
		{ }

		constexpr OperatingSystem(OperatingSystem&& Right) noexcept;

		constexpr ~OperatingSystem() noexcept = default;
	public:
		constexpr OperatingSystem& operator=(const OperatingSystem& Source) noexcept;

		constexpr OperatingSystem& operator=(OperatingSystem&& Right) noexcept;
	public:
		constexpr const PlatformID GetPlatform() const noexcept
		{
			return _PlatformId;
		}

		constexpr const Version& GetVersion() const noexcept
		{
			return _Version;
		}
	public:
		constexpr const bool IsWindows() const noexcept
		{
			return _PlatformId == PlatformID::WindowsCE || _PlatformId == PlatformID::WindowsDesktop || _PlatformId == PlatformID::WindowsPhone ||
				_PlatformId == PlatformID::WindowsServer;
		}
	private:
		PlatformID _PlatformId;
		Version _Version;
	};
}
#endif
