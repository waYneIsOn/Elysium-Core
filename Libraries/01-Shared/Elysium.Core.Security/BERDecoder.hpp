/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_BERDECODER
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_BERDECODER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_IASN1DECODER
#include "IAsn1Decoder.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::Asn1
{
	/*
	class ELYSIUM_CORE_SECURITY_API BERDecoder final : public IAsn1Decoder
	{
	public:
		BERDecoder();
		virtual ~BERDecoder();

		virtual Asn1Identifier DecodeIdentifier(IO::Stream& InputStream) override;

		virtual Asn1Length DecodeLength(IO::Stream& InputStream) override;
	};
	*/
}
#endif