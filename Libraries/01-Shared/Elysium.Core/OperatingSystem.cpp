#include "OperatingSystem.hpp"

Elysium::Core::OperatingSystem::OperatingSystem(const PlatformID & PlatformID, const Version & Version)
	: _PlatformId(PlatformID), _Version(Elysium::Core::Version(Version))
{
}
Elysium::Core::OperatingSystem::~OperatingSystem()
{
}

const Elysium::Core::PlatformID & Elysium::Core::OperatingSystem::GetPlatform() const
{
	return _PlatformId;
}
const Elysium::Core::Version & Elysium::Core::OperatingSystem::GetVersion() const
{
	return _Version;
}
