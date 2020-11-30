/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_DERENCODER
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_DERENCODER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_IASN1DECODER
#include "IAsn1Encoder.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::Encoding::Asn1
{
	// Distinguished Encoding Rules - for instance used in x509certificates
	class ELYSIUM_CORE_SECURITY_API DEREncoder final : public IAsn1Encoder
	{
	public:
		DEREncoder();
		virtual ~DEREncoder();

		virtual void Encode(const Asn1Identifier& Identifier, Elysium::Core::IO::Stream& TargetStream) override;
		virtual void Encode(const Asn1Length& Length, Elysium::Core::IO::Stream& TargetStream) override;
	};
}
#endif
