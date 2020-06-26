/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_OERDECODER
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_OERDECODER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_IASN1DECODER
#include "IAsn1Decoder.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::Asn1
{
	/*
	// Octet Encoding Rules
	class ELYSIUM_CORE_SECURITY_API OERDecoder final : public IAsn1Decoder
	{
	public:
		OERDecoder();
		OERDecoder(const OERDecoder& Source) = delete;
		OERDecoder(OERDecoder&& Right) noexcept = delete;
		virtual ~OERDecoder();

		OERDecoder& operator=(const OERDecoder& Source) = delete;
		OERDecoder& operator=(OERDecoder&& Right) noexcept = delete;

		virtual Asn1Identifier DecodeIdentifier(IO::Stream& InputStream) override;

		virtual Asn1Length DecodeLength(IO::Stream& InputStream) override;
	};
	*/
}
#endif
