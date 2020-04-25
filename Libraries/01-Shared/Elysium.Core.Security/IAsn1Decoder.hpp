/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_IASN1DECODER
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_IASN1DECODER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../Elysium.Core/Array.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_STREAM
#include "../Elysium.Core.IO/Stream.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_ASN1IDENTIFIER
#include "Asn1Identifier.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_ASN1LENGTH
#include "Asn1Length.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_ASN1INTEGER
#include "Asn1Integer.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::Asn1
{
	class ELYSIUM_CORE_SECURITY_API IAsn1Decoder
	{
	public:
		virtual ~IAsn1Decoder() {}

		virtual Asn1Identifier DecodeIdentifier(const Collections::Template::Array<byte>& Data, size_t Offset, size_t Length) = 0;
		virtual Asn1Identifier DecodeIdentifier(IO::Stream& InputStream) = 0;

		virtual Asn1Length DecodeLength(const Collections::Template::Array<byte>& Data, size_t Offset, size_t Length) = 0;
		virtual Asn1Length DecodeLength(IO::Stream& InputStream) = 0;

		//virtual Asn1Boolean

		virtual Asn1Integer DecodeInteger(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const Collections::Template::Array<byte>& Data, size_t Offset, size_t Length) = 0;
		virtual Asn1Integer DecodeInteger(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, IO::Stream& InputStream) = 0;
	};
}
#endif
