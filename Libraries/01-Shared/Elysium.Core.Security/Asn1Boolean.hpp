/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_ASN1BOOLEAN
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_ASN1BOOLEAN

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_ASN1OBJECT
#include "Asn1Object.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::Asn1
{
	class ELYSIUM_CORE_SECURITY_API Asn1Boolean final : public Asn1Object
	{
	public:
		Asn1Boolean(const Asn1Identifier& Identifier, const bool Value);
		virtual ~Asn1Boolean();

		const bool GetValue() const;
	private:
		const bool _Value;
	};
}
#endif
