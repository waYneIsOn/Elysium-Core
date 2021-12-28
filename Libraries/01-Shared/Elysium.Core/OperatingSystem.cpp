#include "OperatingSystem.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::OperatingSystem::OperatingSystem(const PlatformID& PlatformID, const Version& Version) noexcept
	: _PlatformId(PlatformID), _Version(Version)
{ }

Elysium::Core::OperatingSystem::OperatingSystem(const OperatingSystem & Source) noexcept
	: _PlatformId(Source._PlatformId), _Version(Source._Version)
{ }

Elysium::Core::OperatingSystem::OperatingSystem(OperatingSystem&& Right) noexcept
	: _PlatformId(PlatformID::Unknown), _Version()
{
	*this = Elysium::Core::Template::Functional::Move(Right);
}

Elysium::Core::OperatingSystem::~OperatingSystem() noexcept
{ }

Elysium::Core::OperatingSystem& Elysium::Core::OperatingSystem::operator=(const OperatingSystem & Source) noexcept
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

		Right._PlatformId = PlatformID::Unknown;
	}
	return *this;
}

const Elysium::Core::PlatformID Elysium::Core::OperatingSystem::GetPlatform() const
{
	return _PlatformId;
}

const Elysium::Core::Version Elysium::Core::OperatingSystem::GetVersion() const
{
	return _Version;
}
