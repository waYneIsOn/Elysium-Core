/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_OIDCOLLECTION
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_OIDCOLLECTION

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

namespace Elysium::Core::Security::Cryptography
{
	class ELYSIUM_CORE_API OidCollection final
	{
	public:
		OidCollection();
		OidCollection(const OidCollection& Source) = delete;
		OidCollection(OidCollection&& Right) noexcept = delete;
		~OidCollection();

		OidCollection& operator=(const OidCollection& Source) = delete;
		OidCollection& operator=(OidCollection&& Right) noexcept = delete;
	};
}
#endif
