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
		Oid(Elysium::Core::Utf8String&& Value, Elysium::Core::Utf8String&& FriendlyName);

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
	public:
		/// <summary>
		/// 
		/// </summary>
		Oid& operator=(const Oid& Source);

		/// <summary>
		/// 
		/// </summary>
		Oid& operator=(Oid&& Right) noexcept;
	public:
		/// <summary>
		/// 
		/// </summary>
		static Oid FromFriendlyName(const Elysium::Core::Utf8String& FriendlyName, const OidGroup Group);

		/// <summary>
		/// 
		/// </summary>
		static Oid FromOidValue(const Elysium::Core::Utf8String& OidValue, const OidGroup Group);
	public:
		/// <summary>
		/// 
		/// </summary>
		const Elysium::Core::Utf8String& GetValue() const;

		/// <summary>
		/// 
		/// </summary>
		const Elysium::Core::Utf8String& GetFriendlyName() const;
	private:
		Elysium::Core::Utf8String _Value;
		Elysium::Core::Utf8String _FriendlyName;
	};
}
#endif
