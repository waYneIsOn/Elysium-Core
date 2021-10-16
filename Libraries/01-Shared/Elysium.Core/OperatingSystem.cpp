#include "OperatingSystem.hpp"

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core.Template/System.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

#if defined(ELYSIUM_CORE_OS_WINDOWS)
#ifndef _WINDOWS_
#define _WINSOCKAPI_ // don't include winsock
#include <Windows.h>
#endif
#elif defined(ELYSIUM_CORE_OS_ANDROID)

#else
#error "unsupported os"
#endif

Elysium::Core::OperatingSystem::OperatingSystem(const PlatformID& PlatformID, const Version& Version)
	: _PlatformId(PlatformID), _Version(Version)
{ }

Elysium::Core::OperatingSystem::OperatingSystem(const OperatingSystem & Source)
	: _PlatformId(Source._PlatformId), _Version(Source._Version)
{ }

Elysium::Core::OperatingSystem::OperatingSystem(OperatingSystem&& Right) noexcept
	: _PlatformId(PlatformID::Unknown), _Version()
{
	*this = Elysium::Core::Template::Functional::Move(Right);
}

Elysium::Core::OperatingSystem::~OperatingSystem()
{ }

Elysium::Core::OperatingSystem& Elysium::Core::OperatingSystem::operator=(const OperatingSystem & Source)
{
	if (this != &Source)
	{
		_PlatformId = Source._PlatformId;
		_Version = Source._Version;
	}
	return *this;
}

Elysium::Core::OperatingSystem& Elysium::Core::OperatingSystem::operator=(OperatingSystem&& Right) noexcept
{
	if (this != &Right)
	{
		_PlatformId = Elysium::Core::Template::Functional::Move(Right._PlatformId);
		_Version = Elysium::Core::Template::Functional::Move(Right._Version);
	}
	return *this;
}

const Elysium::Core::PlatformID& Elysium::Core::OperatingSystem::GetPlatform() const
{
	return _PlatformId;
}

const Elysium::Core::Version& Elysium::Core::OperatingSystem::GetVersion() const
{
	return _Version;
}
