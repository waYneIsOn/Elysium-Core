#include "OperatingSystem.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

constexpr Elysium::Core::OperatingSystem::OperatingSystem(OperatingSystem&& Right) noexcept
	: _PlatformId(PlatformID::Unknown), _Version()
{
	*this = Elysium::Core::Template::Functional::Move(Right);
}

constexpr Elysium::Core::OperatingSystem& Elysium::Core::OperatingSystem::operator=(const OperatingSystem & Source) noexcept
{
	if (this != &Source)
	{
		_PlatformId = Source._PlatformId;
		_Version = Source._Version;
	}
	return *this;
}

constexpr Elysium::Core::OperatingSystem& Elysium::Core::OperatingSystem::operator=(OperatingSystem&& Right) noexcept
{
	if (this != &Right)
	{
		_PlatformId = Elysium::Core::Template::Functional::Move(Right._PlatformId);
		_Version = Elysium::Core::Template::Functional::Move(Right._Version);

		Right._PlatformId = PlatformID::Unknown;
	}
	return *this;
}
