/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_DERDECODER
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_DERDECODER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_IASN1DECODER
#include "IAsn1Decoder.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::Asn1
{
	class ELYSIUM_CORE_SECURITY_API DERDecoder final : public IAsn1Decoder
	{
	public:
		DERDecoder();
		virtual ~DERDecoder();

		virtual Asn1Identifier DecodeIdentifier(const Collections::Template::Array<byte>& Data, size_t Offset, size_t Length) override;
		virtual Asn1Identifier DecodeIdentifier(IO::Stream& InputStream) override;

		virtual Asn1Length DecodeLength(const Collections::Template::Array<byte>& Data, size_t Offset, size_t Length) override;
		virtual Asn1Length DecodeLength(IO::Stream& InputStream) override;

		virtual Asn1Integer DecodeInteger(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const Collections::Template::Array<byte>& Data, size_t Offset, size_t Length) override;
		virtual Asn1Integer DecodeInteger(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, IO::Stream& InputStream) override;
	private:
		size_t DecodeIdentifierTagNumber(IO::Stream& InputStream, size_t& EncodedLength);
	};
}
#endif
