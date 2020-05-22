/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_ASN1STRING
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_ASN1STRING

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_ASN1OBJECT
#include "Asn1Object.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::Asn1
{
	class ELYSIUM_CORE_SECURITY_API Asn1String final : public Asn1Object
	{
	public:
		Asn1String(const Asn1Identifier& Identifier, const String& Value);
		Asn1String(const Asn1String& Source) = delete;
		Asn1String(Asn1String&& Right) noexcept = delete;
		virtual ~Asn1String();

		Asn1String& operator=(const Asn1String& Source) = delete;
		Asn1String& operator=(Asn1String&& Right) noexcept = delete;

		const String& GetValue() const;
	private:
		const String _Value;
	};
}
#endif
