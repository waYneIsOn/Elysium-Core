/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1LENGTH
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1LENGTH

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "../Elysium.Core.Security/API.hpp"
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::Encoding::Asn1
{
	class ELYSIUM_CORE_SECURITY_API Asn1Length final
	{
	public:
		Asn1Length(const int32_t Length, const int32_t EncodedLength);
		Asn1Length(const Asn1Length& Source) = delete;
		Asn1Length(Asn1Length&& Right) noexcept = delete;
		~Asn1Length();

		Asn1Length& operator=(const Asn1Length& Source) = delete;
		Asn1Length& operator=(Asn1Length&& Right) noexcept = delete;

		const int32_t GetLength() const;
		const int32_t GetEncodedLength() const;
	private:
		const int32_t _Length;
		const int32_t _EncodedLength;
	};
}
#endif
