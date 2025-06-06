/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1BYTEARRAY
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1BYTEARRAY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_CONTAINER_VECTOROFBYTE
#include "../Elysium.Core/VectorOfByte.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "../Elysium.Core.Security/API.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1OBJECT
#include "Asn1Object.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::Encoding::Asn1
{
	class ELYSIUM_CORE_SECURITY_API Asn1ByteArray final : public Asn1Object
	{
	public:
		Asn1ByteArray(const Asn1Identifier & Identifier, Elysium::Core::Container::VectorOfByte&& Data);

		Asn1ByteArray(const Asn1ByteArray& Source) = delete;

		Asn1ByteArray(Asn1ByteArray&& Right) noexcept = delete;

		virtual ~Asn1ByteArray();
	public:
		Asn1ByteArray& operator=(const Asn1ByteArray& Source) = delete;

		Asn1ByteArray& operator=(Asn1ByteArray&& Right) noexcept = delete;
	public:
		const Elysium::Core::Container::VectorOfByte& GetData() const;
	private:
		Elysium::Core::Container::VectorOfByte _Data;
	};
}
#endif
