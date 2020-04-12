/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_ASN1IDENTIFIER
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_ASN1IDENTIFIER

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_ASN1TAGCLASS
#include "Asn1TagClass.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_ASN1TAGNUMBER
#include "Asn1TagNumber.hpp"
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::Asn1
{
	class ELYSIUM_CORE_API Asn1Identifier final
	{
	public:
		Asn1Identifier(const Asn1TagClass TagClass, const bool IsConstructed, const Asn1TagNumber TagNumber, const int32_t EncodedLength);
		Asn1Identifier(const Asn1Identifier& Source);
		Asn1Identifier(Asn1Identifier&& Right) noexcept = delete;
		~Asn1Identifier();

		Asn1Identifier& operator=(const Asn1Identifier& Source) = delete;
		Asn1Identifier& operator=(Asn1Identifier&& Right) noexcept = delete;
	private:
		const Asn1TagClass _TagClass;
		const bool _IsConstructed;
		const Asn1TagNumber _TagNumber;
		const int32_t _EncodedLength;
	};
}
#endif
