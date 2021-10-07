/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_OID
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_OID

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "../Elysium.Core.Security/API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_OIDGROUP
#include "OidGroup.hpp"
#endif

namespace Elysium::Core::Security::Cryptography
{
	/// <summary>
	/// Represents a cryptographic object identifier.
	/// This class cannot be inherited.
	/// </summary>
	class ELYSIUM_CORE_SECURITY_API Oid final
	{
	public:
		/// <summary>
		/// 
		/// </summary>
		Oid();

		/// <summary>
		/// 
		/// </summary>
		Oid(Elysium::Core::String&& Value, Elysium::Core::String&& FriendlyName);

		/// <summary>
		/// 
		/// </summary>
		Oid(const Oid& Source);

		/// <summary>
		/// 
		/// </summary>
		Oid(Oid&& Right) noexcept;

		/// <summary>
		/// 
		/// </summary>
		~Oid();

		/// <summary>
		/// 
		/// </summary>
		Oid& operator=(const Oid& Source);

		/// <summary>
		/// 
		/// </summary>
		Oid& operator=(Oid&& Right) noexcept;

		/// <summary>
		/// 
		/// </summary>
		static Oid FromFriendlyName(const Elysium::Core::String& FriendlyName, const OidGroup Group);

		/// <summary>
		/// 
		/// </summary>
		static Oid FromOidValue(const Elysium::Core::String& OidValue, const OidGroup Group);

		/// <summary>
		/// 
		/// </summary>
		const Elysium::Core::String& GetValue() const;

		/// <summary>
		/// 
		/// </summary>
		const Elysium::Core::String& GetFriendlyName() const;
	private:
		Elysium::Core::String _Value;
		Elysium::Core::String _FriendlyName;
	};
}
#endif
