/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1OBJECTIDENTIFIER
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1OBJECTIDENTIFIER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "../Elysium.Core.Security/API.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_OID
#include "Oid.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1OBJECT
#include "Asn1Object.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::Encoding::Asn1
{
	class ELYSIUM_CORE_SECURITY_API Asn1ObjectIdentifier : public Asn1Object
	{
	public:
		Asn1ObjectIdentifier(const Asn1Identifier& Identifier, const Oid& Value);
		Asn1ObjectIdentifier(const Asn1ObjectIdentifier& Source);
		Asn1ObjectIdentifier(Asn1ObjectIdentifier&& Right) noexcept;
		virtual ~Asn1ObjectIdentifier();

		Asn1ObjectIdentifier& operator=(const Asn1ObjectIdentifier& Source);
		Asn1ObjectIdentifier& operator=(Asn1ObjectIdentifier&& Right) noexcept;

		const Oid& GetValue() const;
	private:
		Oid _Value;
	};
}
#endif
