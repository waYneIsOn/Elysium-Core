/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_OIDREPOSITORY
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_OIDREPOSITORY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "../Elysium.Core.Security/API.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_OIDGROUP
#include "OidGroup.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_OIDNODE
#include "OidNode.hpp"
#endif

namespace Elysium::Core::Security::Cryptography
{
	/// <summary>
	/// Fallback functionality for looking up object identifiers if an os doesn't offer it.
	/// http://oid-info.com/
	/// </summary>
	class ELYSIUM_CORE_SECURITY_API OidRepository final
	{
	public:
		OidRepository() = delete;
		OidRepository(const OidRepository& Source) = delete;
		OidRepository(OidRepository&& Right) noexcept = delete;
		~OidRepository() = delete;

		OidRepository& operator=(const OidRepository& Source) = delete;
		OidRepository& operator=(OidRepository&& Right) noexcept = delete;

		//static OidNode FromFriendlyName(const Elysium::Core::Utf8String& FriendlyName, const OidGroup Group);
		//static OidNode FromOidValue(const Elysium::Core::Utf8String& OidValue, const OidGroup Group);
	private:
		/*
		inline static const OidNode _InternationalTelecommunication = OidNode(0, u8"itu-t");
		inline static const OidNode _InternationalOrganizationForStandardization = OidNode(1, u8"iso");
		inline static const OidNode _AreasOfJointWork = OidNode(2, u8"joint-iso-itu-t");
		*/
	};
}
#endif
