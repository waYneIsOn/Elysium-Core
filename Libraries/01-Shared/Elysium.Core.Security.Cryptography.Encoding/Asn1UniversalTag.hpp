/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1UNIVERSALTAG
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1UNIVERSALTAG

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::Encoding::Asn1
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class Asn1UniversalTag : uint8_t
#elif defined(__ANDROID__)
	enum class Asn1UniversalTag
#else
#error "undefined os"
#endif
	{
		// simple types
		EndOfContent = 0x00,
		Boolean = 0x01,
		Integer = 0x02,
		BitString = 0x03,
		OctetString = 0x04,
		Null = 0x05,
		ObjectIdentifier = 0x06,
		ObjectDescriptor = 0x07,
		External = 0x08,
		Single = 0x09,
		Enumerated = 0x0A,
		EmbeddedPdv = 0x0B,
		UTF8String = 0x0C,
		RelativeOid = 0x0D,
		Time = 0x0E,

		Reserverd = 0x0F,

		// structured types
		Sequence = 0x10,
		SequenceOf = Sequence,
		Set = 0x11,
		SetOf = Set,

		// string types
		NumericString = 0x12,
		PrintableString = 0x13,
		TeletexString = 0x14,   // T61String
		VideotexString = 0x15,
		IA5String = 0x16,
		UTCTime = 0x17,
		GeneralizedTime = 0x18,
		GraphicString = 0x19,
		VisibleString = 0x1A,   // ISO646String
		GeneralString = 0x1B,
		UniversalString = 0x1C,
		CharacterString = 0x1D,
		BmpString = 0x1E,
		Date = 0x1F,
		TimeOfDay = 0x20,
		DateTime = 0x21,
		Duration = 0x22,
		OidIri = 0x23,
		RelativeOidIri = 0x24,
	};
}
#endif
