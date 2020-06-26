/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_LBERDECODER
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_LBERDECODER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_IASN1DECODER
#include "IAsn1Decoder.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::Asn1
{
	/*
	// Lightweight Basic Encoding Rules - for instance used when communicating with eDirectory
	class ELYSIUM_CORE_SECURITY_API LBERDecoder final : public IAsn1Decoder
	{
	public:
		LBERDecoder();
		LBERDecoder(const LBERDecoder& Source) = delete;
		LBERDecoder(LBERDecoder&& Right) noexcept = delete;
		virtual ~LBERDecoder();

		LBERDecoder& operator=(const LBERDecoder& Source) = delete;
		LBERDecoder& operator=(LBERDecoder&& Right) noexcept = delete;

		virtual Asn1Identifier DecodeIdentifier(IO::Stream& InputStream) override;

		virtual Asn1Length DecodeLength(IO::Stream& InputStream) override;
	};
	*/
}
#endif
