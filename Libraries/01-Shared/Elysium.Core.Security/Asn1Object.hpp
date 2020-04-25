/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_ASN1OBJECT
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_ASN1OBJECT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_ASN1IDENTIFIER
#include "Asn1Identifier.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::Asn1
{
	class ELYSIUM_CORE_SECURITY_API Asn1Object
	{
	public:
		Asn1Object(const Asn1Object& Source) = delete;
		Asn1Object(Asn1Object&& Right) noexcept = delete;
		virtual ~Asn1Object();

		Asn1Object& operator=(const Asn1Object& Source) = delete;
		Asn1Object& operator=(Asn1Object&& Right) noexcept = delete;
	protected:
		Asn1Object(const Asn1Identifier& Identifier);
	private:
		Asn1Identifier _Identifier;
	};
}
#endif
