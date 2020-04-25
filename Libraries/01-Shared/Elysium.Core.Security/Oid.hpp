/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_OID
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_OID

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_OIDGROUP
#include "OidGroup.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_SYSTEM
#include "System.hpp"
#endif

namespace Elysium::Core::Security::Cryptography
{
	class ELYSIUM_CORE_SECURITY_API Oid final
	{
	public:
		Oid(const Oid& Source) = delete;
		Oid(Oid&& Right) noexcept = delete;
		~Oid();

		static Oid FromFriendlyName(const WideString& FriendlyName, const OidGroup Group);
		static Oid FromOidValue(const CharString& OidValue, const OidGroup Group);

		Oid& operator=(const Oid& Source) = delete;
		Oid& operator=(Oid&& Right) noexcept = delete;

		const WideString GetFriendlyName() const;
		const CharString GetValue() const;
	private:
		Oid(const ELYSIUM_CORE_SECURITY_CRYPTOHRAPHY_OIDPOINTER NativeOid);

		const ELYSIUM_CORE_SECURITY_CRYPTOHRAPHY_OIDPOINTER _NativeOid = nullptr;
	};
}
#endif
