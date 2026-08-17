/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1TAG
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1TAG

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "../../Elysium.Core.Security/API.hpp"
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

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1INTEGER
#include "Asn1Integer.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1NULL
#include "Asn1Null.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1UTF8STRING
#include "Asn1Utf8String.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1TAG
#include "../../Elysium.Core.Template/Security/Cryptography/Encoding/Asn1/Asn1Tag.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::Encoding::Asn1
{
	template class ELYSIUM_CORE_SECURITY_API Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1Tag<Asn1Boolean>;
	template class ELYSIUM_CORE_SECURITY_API Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1Tag<Asn1ByteArray>;
	template class ELYSIUM_CORE_SECURITY_API Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1Tag<Asn1DateTime>;
	template class ELYSIUM_CORE_SECURITY_API Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1Tag<Asn1Integer>;
	template class ELYSIUM_CORE_SECURITY_API Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1Tag<Asn1Null>;
	template class ELYSIUM_CORE_SECURITY_API Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1Tag<Asn1Utf8String>;

	using Asn1TagBoolean = Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1Tag<Asn1Boolean>;
	using Asn1TagByteArray = Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1Tag<Asn1ByteArray>;
	using Asn1TagDateTime = Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1Tag<Asn1DateTime>;
	using Asn1TagInteger = Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1Tag<Asn1Integer>;
	using Asn1TagNull = Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1Tag<Asn1Null>;
	using Asn1TagString = Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1Tag<Asn1Utf8String>;
}
#endif
