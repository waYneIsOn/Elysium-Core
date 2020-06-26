/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_IASN1ENCODER
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_IASN1ENCODER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "../Elysium.Core.Security/API.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_STREAM
#include "../Elysium.Core.IO/Stream.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1IDENTIFIER
#include "Asn1Identifier.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1LENGTH
#include "Asn1Length.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::Encoding::Asn1
{
	class ELYSIUM_CORE_SECURITY_API IAsn1Encoder
	{
	public:
		virtual ~IAsn1Encoder() {}

		virtual void Encode(const Asn1Identifier& Identifier, Elysium::Core::IO::Stream& TargetStream) = 0;
		virtual void Encode(const Asn1Length& Length, Elysium::Core::IO::Stream& TargetStream) = 0;

		/*
		virtual Asn1Length DecodeLength(const Collections::Template::Array<byte>& Data, size_t Offset, size_t Length) = 0;
		virtual Asn1Length DecodeLength(IO::Stream& InputStream) = 0;

		virtual Asn1Boolean DecodeBoolean(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const Collections::Template::Array<byte>& Data, size_t Offset, size_t Length) = 0;
		virtual Asn1Boolean DecodeBoolean(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, IO::Stream& InputStream) = 0;

		virtual Asn1Integer DecodeInteger(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const Collections::Template::Array<byte>& Data, size_t Offset, size_t Length) = 0;
		virtual Asn1Integer DecodeInteger(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, IO::Stream& InputStream) = 0;

		virtual Asn1ObjectIdentifier DecodeObjectIdentifier(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const Collections::Template::Array<byte>& Data, size_t Offset, size_t Length) = 0;
		virtual Asn1ObjectIdentifier DecodeObjectIdentifier(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, IO::Stream& InputStream) = 0;

		virtual Asn1String DecodeString(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const Collections::Template::Array<byte>& Data, size_t Offset, size_t Length) = 0;
		virtual Asn1String DecodeString(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, IO::Stream& InputStream) = 0;
		*/
	};
}
#endif
