/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_PERDECODER
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_PERDECODER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_IASN1DECODER
#include "IAsn1Decoder.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::Encoding::Asn1
{
	/*
	// Packed Encoding Rules
	class ELYSIUM_CORE_SECURITY_API PERDecoder final : public IAsn1Decoder
	{
	public:
		PERDecoder();
		PERDecoder(const PERDecoder& Source) = delete;
		PERDecoder(PERDecoder&& Right) noexcept = delete;
		virtual ~PERDecoder();

		PERDecoder& operator=(const PERDecoder& Source) = delete;
		PERDecoder& operator=(PERDecoder&& Right) noexcept = delete;

		virtual Asn1Identifier DecodeIdentifier(IO::Stream& InputStream) override;

		virtual Asn1Length DecodeLength(IO::Stream& InputStream) override;
	};
	*/
}
#endif
