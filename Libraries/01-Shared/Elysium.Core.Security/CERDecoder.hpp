/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_CERDECODER
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_CERDECODER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_IASN1DECODER
#include "IAsn1Decoder.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::Asn1
{
	/*
	// Caninocal Encoding Rules
	class ELYSIUM_CORE_SECURITY_API CERDecoder final : public IAsn1Decoder
	{
	public:
		CERDecoder();
		CERDecoder(const CERDecoder& Source) = delete;
		CERDecoder(CERDecoder&& Right) noexcept = delete;
		virtual ~CERDecoder();

		CERDecoder& operator=(const CERDecoder& Source) = delete;
		CERDecoder& operator=(CERDecoder&& Right) noexcept = delete;

		virtual Asn1Identifier DecodeIdentifier(IO::Stream& InputStream) override;

		virtual Asn1Length DecodeLength(IO::Stream& InputStream) override;
	};
	*/
}
#endif