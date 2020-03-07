/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_OID
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_OID

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_OIDGROUP
#include "OidGroup.hpp"
#endif

namespace Elysium::Core::Security::Cryptography
{
	class ELYSIUM_CORE_API Oid final
	{
	public:
		Oid();
		Oid(const Oid& Source) = delete;
		Oid(Oid&& Right) noexcept = delete;
		~Oid();

		static Oid FromFriendlyName(const String& FriendlyName, const OidGroup Group);
		static Oid FromOidValue(const String& OidValue, const OidGroup Group);

		Oid& operator=(const Oid& Source) = delete;
		Oid& operator=(Oid&& Right) noexcept = delete;

		const String GetFriendlyName() const;
		const String GetValue() const;

		void SetFriendlyName(const String& Value);
		void SetFriendlyName(String&& Value);
		void SetValue(const String& Value);
		void SetValue(String&& Value);
	private:
		String _FriendlyName;
		String _Value;
	};
}
#endif
