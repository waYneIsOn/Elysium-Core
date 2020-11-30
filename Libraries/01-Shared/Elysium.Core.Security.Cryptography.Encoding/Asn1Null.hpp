/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1NULL
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1NULL

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
	class ELYSIUM_CORE_SECURITY_API Asn1Null : public Asn1Object
	{
	public:
		Asn1Null();
		Asn1Null(const Asn1Null& Source) = delete;
		Asn1Null(Asn1Null&& Right) noexcept = delete;
		virtual ~Asn1Null();

		Asn1Null& operator=(const Asn1Null& Source) = delete;
		Asn1Null& operator=(Asn1Null&& Right) noexcept = delete;
	};
}
#endif
