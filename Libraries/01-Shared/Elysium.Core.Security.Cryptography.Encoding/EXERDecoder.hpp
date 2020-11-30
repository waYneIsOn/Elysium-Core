/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_EXERDECODER
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_EXERDECODER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_IASN1DECODER
#include "IAsn1Decoder.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::Encoding::Asn1
{
	/*
	// Extended XML Encoding Rules
	class ELYSIUM_CORE_SECURITY_API EXERDecoder final : public IAsn1Decoder
	{
	public:
		EXERDecoder();
		EXERDecoder(const EXERDecoder& Source) = delete;
		EXERDecoder(EXERDecoder&& Right) noexcept = delete;
		virtual ~EXERDecoder();

		EXERDecoder& operator=(const EXERDecoder& Source) = delete;
		EXERDecoder& operator=(EXERDecoder&& Right) noexcept = delete;

		virtual Asn1Identifier DecodeIdentifier(IO::Stream& InputStream) override;

		virtual Asn1Length DecodeLength(IO::Stream& InputStream) override;
	};
	*/
}
#endif
