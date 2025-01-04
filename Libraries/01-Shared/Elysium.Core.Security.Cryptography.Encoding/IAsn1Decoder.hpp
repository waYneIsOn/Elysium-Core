/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_IASN1DECODER
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_IASN1DECODER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_IO_STREAM
#include "../Elysium.Core.IO/Stream.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "../Elysium.Core.Security/API.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1BOOLEAN
#include "Asn1Boolean.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1BYTEARRAY
#include "Asn1ByteArray.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1DATETIME
#include "Asn1DateTime.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1IDENTIFIER
#include "Asn1Identifier.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1INTEGER
#include "Asn1Integer.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1LENGTH
#include "Asn1Length.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1OBJECTIDENTIFIER
#include "Asn1ObjectIdentifier.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1STRING
#include "Asn1String.hpp"
#endif

#ifndef ELYSIUM_CORE_CONTAINER_VECTOROFBYTE
#include "../Elysium.Core/VectorOfByte.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::Encoding::Asn1
{
	class ELYSIUM_CORE_SECURITY_API IAsn1Decoder
	{
	public:
		virtual ~IAsn1Decoder() {}
	public:
		virtual Asn1Identifier DecodeIdentifier(const Elysium::Core::Container::VectorOfByte& Data, const Elysium::Core::size Offset, const Elysium::Core::size Length) = 0;
		virtual Asn1Identifier DecodeIdentifier(const byte* Data, const Elysium::Core::size Length) = 0;
		virtual Asn1Identifier DecodeIdentifier(IO::Stream& InputStream) = 0;

		virtual Asn1Length DecodeLength(const Elysium::Core::Container::VectorOfByte& Data, const Elysium::Core::size Offset, const Elysium::Core::size Length) = 0;
		virtual Asn1Length DecodeLength(const byte* Data, const Elysium::Core::size Length) = 0;
		virtual Asn1Length DecodeLength(IO::Stream& InputStream) = 0;

		virtual Asn1ByteArray DecodeByteArray(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const Elysium::Core::Container::VectorOfByte& Data, const Elysium::Core::size Offset, const Elysium::Core::size Length) = 0;
		virtual Asn1ByteArray DecodeByteArray(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const byte* Data, const Elysium::Core::size Length) = 0;
		virtual Asn1ByteArray DecodeByteArray(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, IO::Stream& InputStream) = 0;

		virtual Asn1Boolean DecodeBoolean(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const Elysium::Core::Container::VectorOfByte& Data, const Elysium::Core::size Offset, const Elysium::Core::size Length) = 0;
		virtual Asn1Boolean DecodeBoolean(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const byte* Data, const Elysium::Core::size Length) = 0;
		virtual Asn1Boolean DecodeBoolean(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, IO::Stream& InputStream) = 0;

		virtual Asn1Integer DecodeInteger(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const Elysium::Core::Container::VectorOfByte& Data, const Elysium::Core::size Offset, const Elysium::Core::size Length) = 0;
		virtual Asn1Integer DecodeInteger(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const byte* Data, const Elysium::Core::size Length) = 0;
		virtual Asn1Integer DecodeInteger(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, IO::Stream& InputStream) = 0;

		virtual Asn1ObjectIdentifier DecodeObjectIdentifier(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const Elysium::Core::Container::VectorOfByte& Data, const Elysium::Core::size Offset, const Elysium::Core::size Length) = 0;
		virtual Asn1ObjectIdentifier DecodeObjectIdentifier(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const byte* Data, const Elysium::Core::size Length) = 0;
		virtual Asn1ObjectIdentifier DecodeObjectIdentifier(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, IO::Stream& InputStream) = 0;

		virtual Asn1String DecodeString(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const Elysium::Core::Container::VectorOfByte& Data, const Elysium::Core::size Offset, const Elysium::Core::size Length) = 0;
		virtual Asn1String DecodeString(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const byte* Data, const Elysium::Core::size Length) = 0;
		virtual Asn1String DecodeString(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, IO::Stream& InputStream) = 0;

		virtual Asn1DateTime DecodeDateTime(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const Elysium::Core::Container::VectorOfByte& Data, const Elysium::Core::size Offset, const Elysium::Core::size Length) = 0;
		virtual Asn1DateTime DecodeDateTime(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const byte* Data, const Elysium::Core::size Length) = 0;
		virtual Asn1DateTime DecodeDateTime(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, IO::Stream& InputStream) = 0;
	};
}
#endif
