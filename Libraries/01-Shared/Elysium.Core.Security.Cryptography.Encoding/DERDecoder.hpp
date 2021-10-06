/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_DERDECODER
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_DERDECODER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_IASN1DECODER
#include "IAsn1Decoder.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::Encoding::Asn1
{
	// Distinguished Encoding Rules - for instance used in x509certificates
	class ELYSIUM_CORE_SECURITY_API DERDecoder final : public IAsn1Decoder
	{
	public:
		DERDecoder();
		virtual ~DERDecoder();

		virtual Asn1Identifier DecodeIdentifier(const Collections::Template::Array<byte>& Data, const size_t Offset, const size_t Length) override;
		virtual Asn1Identifier DecodeIdentifier(const byte* Data, const size_t Length) override;
		virtual Asn1Identifier DecodeIdentifier(IO::Stream& InputStream) override;

		virtual Asn1Length DecodeLength(const Collections::Template::Array<byte>& Data, const size_t Offset, const size_t Length) override;
		virtual Asn1Length DecodeLength(const byte* Data, const size_t Length) override;
		virtual Asn1Length DecodeLength(IO::Stream& InputStream) override;

		virtual Asn1ByteArray DecodeByteArray(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const Collections::Template::Array<byte>& Data, const size_t Offset, const size_t Length) override;
		virtual Asn1ByteArray DecodeByteArray(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const byte* Data, const size_t Length) override;
		virtual Asn1ByteArray DecodeByteArray(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, IO::Stream& InputStream) override;

		virtual Asn1Boolean DecodeBoolean(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const Collections::Template::Array<byte>& Data, const size_t Offset, const size_t Length) override;
		virtual Asn1Boolean DecodeBoolean(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const byte* Data, const size_t Length) override;
		virtual Asn1Boolean DecodeBoolean(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, IO::Stream& InputStream) override;

		virtual Asn1Integer DecodeInteger(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const Collections::Template::Array<byte>& Data, const size_t Offset, const size_t Length) override;
		virtual Asn1Integer DecodeInteger(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const byte* Data, const size_t Length) override;
		virtual Asn1Integer DecodeInteger(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, IO::Stream& InputStream) override;

		virtual Asn1ObjectIdentifier DecodeObjectIdentifier(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const Collections::Template::Array<byte>& Data, const size_t Offset, const size_t Length) override;
		virtual Asn1ObjectIdentifier DecodeObjectIdentifier(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const byte* Data, const size_t Length) override;
		virtual Asn1ObjectIdentifier DecodeObjectIdentifier(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, IO::Stream& InputStream) override;

		virtual Asn1String DecodeString(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const Collections::Template::Array<byte>& Data, const size_t Offset, const size_t Length) override;
		virtual Asn1String DecodeString(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const byte* Data, const size_t Length) override;
		virtual Asn1String DecodeString(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, IO::Stream& InputStream) override;

		virtual Asn1DateTime DecodeDateTime(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const Collections::Template::Array<byte>& Data, const size_t Offset, const size_t Length) override;
		virtual Asn1DateTime DecodeDateTime(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const byte* Data, const size_t Length) override;
		virtual Asn1DateTime DecodeDateTime(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, IO::Stream& InputStream) override;
	private:
		const size_t DecodeIdentifierTagNumber(IO::Stream& InputStream, Elysium::Core::int32_t EncodedLength);
	};
}
#endif
