/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_OPERATINGSYSTEM
#define ELYSIUM_CORE_OPERATINGSYSTEM

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_PLATFORMID
#include "PlatformID.hpp"
#endif

#ifndef ELYSIUM_CORE_VERSION
#include "Version.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		class ELYSIUM_CORE_API OperatingSystem final
		{
		public:
			OperatingSystem(const PlatformID& PlatformID, const Version& Version);
			~OperatingSystem();

			const PlatformID& GetPlatform() const;
			const Version& GetVersion() const;
		private:
			const PlatformID _PlatformId;
			const Version _Version;
		};
	}
}
#endif
