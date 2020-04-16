/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_OIDCOLLECTION
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_OIDCOLLECTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_OID
#include "Oid.hpp"
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
	private:
		size_t _Capacity;
		size_t _Count;
		Oid* _Data;
	};
}
#endif
