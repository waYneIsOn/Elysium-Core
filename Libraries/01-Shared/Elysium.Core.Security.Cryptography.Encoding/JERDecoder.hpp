/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_JERDECODER
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_JERDECODER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_IASN1DECODER
#include "IAsn1Decoder.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::Encoding::Asn1
{
	/*
	// JSON Encoding Rules
	class ELYSIUM_CORE_SECURITY_API JERDecoder final : public IAsn1Decoder
	{
	public:
		JERDecoder();
		JERDecoder(const JERDecoder& Source) = delete;
		JERDecoder(JERDecoder&& Right) noexcept = delete;
		virtual ~JERDecoder();

		JERDecoder& operator=(const JERDecoder& Source) = delete;
		JERDecoder& operator=(JERDecoder&& Right) noexcept = delete;

		virtual Asn1Identifier DecodeIdentifier(IO::Stream& InputStream) override;

		virtual Asn1Length DecodeLength(IO::Stream& InputStream) override;
	};
	*/
}
#endif
