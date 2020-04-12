/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_ASN1LENGTH
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_ASN1LENGTH

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::Asn1
{
	class ELYSIUM_CORE_API Asn1Length final
	{
	public:
		Asn1Length(const int32_t Length, const int32_t EncodedLength);
		Asn1Length(const Asn1Length& Source) = delete;
		Asn1Length(Asn1Length&& Right) noexcept = delete;
		~Asn1Length();

		Asn1Length& operator=(const Asn1Length& Source) = delete;
		Asn1Length& operator=(Asn1Length&& Right) noexcept = delete;
	private:
		const int32_t _Length;
		const int32_t _EncodedLength;
	};
}
#endif
