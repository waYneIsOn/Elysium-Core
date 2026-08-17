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

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_BERDECODER
#include "../../Elysium.Core.Template/Security/Cryptography/Encoding/Asn1/BERDecoder.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_VALIDATION_BERVALIDATOR
#include "../../Elysium.Core.Template/Security/Cryptography/Encoding/Asn1/Validation/BERValidator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_VALIDATION_CERVALIDATOR
#include "../../Elysium.Core.Template/Security/Cryptography/Encoding/Asn1/Validation/CERValidator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_VALIDATION_DERVALIDATOR
#include "../../Elysium.Core.Template/Security/Cryptography/Encoding/Asn1/Validation/DERValidator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_VALIDATION_LBERVALIDATOR
#include "../../Elysium.Core.Template/Security/Cryptography/Encoding/Asn1/Validation/LBERValidator.hpp"
#endif




#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_IASN1DECODER
#include "IAsn1Decoder.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::Encoding::Asn1
{
	template class ELYSIUM_CORE_SECURITY_API
		Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::BERDecoder<Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Validation::BERValidator>;
	template class ELYSIUM_CORE_SECURITY_API
		Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::BERDecoder<Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Validation::CERValidator>;
	/*
	template class ELYSIUM_CORE_SECURITY_API
		Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::BERDecoder<Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Validation::DERValidator>;
	*/
	template class ELYSIUM_CORE_SECURITY_API
		Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::BERDecoder<Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Validation::LBERValidator>;

	using BERDecoder =
		Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::BERDecoder<Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Validation::BERValidator>;
	using CERDecoder =
		Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::BERDecoder<Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Validation::CERValidator>;
	/*
	using DERDecoder =
		Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::BERDecoder<Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Validation::DERValidator>;
	*/
	using LBERDecoder =
		Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::BERDecoder<Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Validation::LBERValidator>;





	// Distinguished Encoding Rules - for instance used in x509certificates
	class ELYSIUM_CORE_SECURITY_API DERDecoder final : public IAsn1Decoder
	{
	public:
		DERDecoder();

		virtual ~DERDecoder();
	public:
		virtual Asn1Identifier DecodeIdentifier(const Elysium::Core::Container::VectorOfByte& Data, const Elysium::Core::size Offset, const Elysium::Core::size Length) override;
		virtual Asn1Identifier DecodeIdentifier(const byte* Data, const Elysium::Core::size Length) override;
		virtual Asn1Identifier DecodeIdentifier(IO::Stream& InputStream) override;

		virtual Asn1Length DecodeLength(const Elysium::Core::Container::VectorOfByte& Data, const Elysium::Core::size Offset, const Elysium::Core::size Length) override;
		virtual Asn1Length DecodeLength(const byte* Data, const Elysium::Core::size Length) override;
		virtual Asn1Length DecodeLength(IO::Stream& InputStream) override;

		virtual Asn1ByteArray DecodeByteArray(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const Elysium::Core::Container::VectorOfByte& Data, const Elysium::Core::size Offset, const Elysium::Core::size Length) override;
		virtual Asn1ByteArray DecodeByteArray(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const byte* Data, const Elysium::Core::size Length) override;
		virtual Asn1ByteArray DecodeByteArray(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, IO::Stream& InputStream) override;

		virtual Asn1Boolean DecodeBoolean(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const Elysium::Core::Container::VectorOfByte& Data, const Elysium::Core::size Offset, const Elysium::Core::size Length) override;
		virtual Asn1Boolean DecodeBoolean(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const byte* Data, const Elysium::Core::size Length) override;
		virtual Asn1Boolean DecodeBoolean(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, IO::Stream& InputStream) override;

		virtual Asn1Integer DecodeInteger(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const Elysium::Core::Container::VectorOfByte& Data, const Elysium::Core::size Offset, const Elysium::Core::size Length) override;
		virtual Asn1Integer DecodeInteger(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const byte* Data, const Elysium::Core::size Length) override;
		virtual Asn1Integer DecodeInteger(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, IO::Stream& InputStream) override;

		virtual Asn1ObjectIdentifier DecodeObjectIdentifier(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const Elysium::Core::Container::VectorOfByte& Data, const Elysium::Core::size Offset, const Elysium::Core::size Length) override;
		virtual Asn1ObjectIdentifier DecodeObjectIdentifier(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const byte* Data, const Elysium::Core::size Length) override;
		virtual Asn1ObjectIdentifier DecodeObjectIdentifier(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, IO::Stream& InputStream) override;

		virtual Asn1Utf8String DecodeString(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const Elysium::Core::Container::VectorOfByte& Data, const Elysium::Core::size Offset, const Elysium::Core::size Length) override;
		virtual Asn1Utf8String DecodeString(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const byte* Data, const Elysium::Core::size Length) override;
		virtual Asn1Utf8String DecodeString(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, IO::Stream& InputStream) override;

		virtual Asn1DateTime DecodeDateTime(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const Elysium::Core::Container::VectorOfByte& Data, const Elysium::Core::size Offset, const Elysium::Core::size Length) override;
		virtual Asn1DateTime DecodeDateTime(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const byte* Data, const Elysium::Core::size Length) override;
		virtual Asn1DateTime DecodeDateTime(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, IO::Stream& InputStream) override;
	private:
		const Elysium::Core::size DecodeIdentifierTagNumber(IO::Stream& InputStream, Elysium::Core::int32_t& EncodedLength);
	};
}
#endif
