/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_XERDECODER
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_XERDECODER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_IASN1DECODER
#include "IAsn1Decoder.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::Encoding::Asn1
{
	/*
	// XML Encoding Rules
	class ELYSIUM_CORE_SECURITY_API XERDecoder final : public IAsn1Decoder
	{
	public:
		XERDecoder();
		XERDecoder(const XERDecoder& Source) = delete;
		XERDecoder(XERDecoder&& Right) noexcept = delete;
		virtual ~XERDecoder();

		XERDecoder& operator=(const XERDecoder& Source) = delete;
		XERDecoder& operator=(XERDecoder&& Right) noexcept = delete;

		virtual Asn1Identifier DecodeIdentifier(IO::Stream& InputStream) override;

		virtual Asn1Length DecodeLength(IO::Stream& InputStream) override;
	};
	*/
}
#endif
