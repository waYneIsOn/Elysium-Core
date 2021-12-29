/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1STRING
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1STRING

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "../Elysium.Core.Security/API.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1OBJECT
#include "Asn1Object.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::Encoding::Asn1
{
	class ELYSIUM_CORE_SECURITY_API Asn1String final : public Asn1Object
	{
	public:
		Asn1String(const Asn1Identifier& Identifier, Elysium::Core::Utf8String&& Value);

		Asn1String(const Asn1String& Source) = delete;

		Asn1String(Asn1String&& Right) noexcept = delete;

		virtual ~Asn1String();
	public:
		Asn1String& operator=(const Asn1String& Source) = delete;

		Asn1String& operator=(Asn1String&& Right) noexcept = delete;
	public:
		const Elysium::Core::Utf8String& GetValue() const;
	private:
		Elysium::Core::Utf8String _Value;
	};
}
#endif
