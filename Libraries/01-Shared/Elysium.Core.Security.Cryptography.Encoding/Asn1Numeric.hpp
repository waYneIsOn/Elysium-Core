/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1NUMERIC
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1NUMERIC

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "../Elysium.Core.Security/API.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1OBJECT
#include "Asn1Object.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::Encoding::Asn1
{
	class ELYSIUM_CORE_SECURITY_API Asn1Numeric : public Asn1Object
	{
	public:
		Asn1Numeric(const Asn1Numeric& Source) = delete;
		Asn1Numeric(Asn1Numeric&& Right) noexcept = delete;
		virtual ~Asn1Numeric();

		Asn1Numeric& operator=(const Asn1Numeric& Source) = delete;
		Asn1Numeric& operator=(Asn1Numeric&& Right) noexcept = delete;
	protected:
		Asn1Numeric(const Asn1Identifier& Identifier);
	};
}
#endif
