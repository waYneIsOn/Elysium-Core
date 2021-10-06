/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1DATETIME
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1DATETIME

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "../Elysium.Core.Security/API.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1OBJECT
#include "Asn1Object.hpp"
#endif

#ifndef ELYSIUM_CORE_DATETIME
#include "../Elysium.Core/DateTime.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::Encoding::Asn1
{
	class ELYSIUM_CORE_SECURITY_API Asn1DateTime final : public Asn1Object
	{
	public:
		Asn1DateTime(const Asn1Identifier & Identifier, const DateTime& Value);
		Asn1DateTime(const Asn1DateTime& Source) = delete;
		Asn1DateTime(Asn1DateTime&& Right) noexcept = delete;
		virtual ~Asn1DateTime();

		Asn1DateTime& operator=(const Asn1DateTime& Source) = delete;
		Asn1DateTime& operator=(Asn1DateTime&& Right) noexcept = delete;

		const DateTime& GetValue() const;
	private:
		const DateTime _Value;
	};
}
#endif
