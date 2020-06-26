/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1IDENTIFIER
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1IDENTIFIER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "../Elysium.Core.Security/API.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1TAGCLASS
#include "Asn1TagClass.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1UNIVERSALTAG
#include "Asn1UniversalTag.hpp"
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::Encoding::Asn1
{
	class ELYSIUM_CORE_SECURITY_API Asn1Identifier final
	{
	public:
		Asn1Identifier(const Asn1TagClass TagClass, const bool IsConstructed, const Asn1UniversalTag TagNumber, const int32_t EncodedLength);
		Asn1Identifier(const Asn1TagClass TagClass, const bool IsConstructed, const int32_t TagNumber, const int32_t EncodedLength);
		Asn1Identifier(const Asn1TagClass TagClass, const bool IsConstructed, const Asn1UniversalTag TagNumber);
		Asn1Identifier(const Asn1TagClass TagClass, const bool IsConstructed, const int32_t TagNumber);
		Asn1Identifier(const Asn1Identifier& Source);
		Asn1Identifier(Asn1Identifier&& Right) noexcept = delete;
		~Asn1Identifier();

		const Asn1TagClass GetTagClass() const;
		const bool GetIsConstructed() const;
		const int32_t GetTagNumber() const;
		const int32_t GetEncodedLength() const;

		Asn1Identifier& operator=(const Asn1Identifier& Source) = delete;
		Asn1Identifier& operator=(Asn1Identifier&& Right) noexcept = delete;
	private:
		const Asn1TagClass _TagClass;
		const bool _IsConstructed;
		const int32_t _TagNumber;
		const int32_t _EncodedLength;
	};
}
#endif
