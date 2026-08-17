/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_BERDECODER
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_BERDECODER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_ARGUMENTEXCEPTION
#include "../../Elysium.Core/ArgumentException.hpp"
#endif

#ifndef ELYSIUM_CORE_ARGUMENTNULLEXCEPTION
#include "../../Elysium.Core/ArgumentNullException.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_STRINGVIEW
#include "../../Elysium.Core/StringView.hpp"
#endif

#ifndef ELYSIUM_CORE_CONTAINER_VECTOROFBYTE
#include "../../Elysium.Core/VectorOfByte.hpp"
#endif

#ifndef ELYSIUM_CORE_CONTAINER_VIEW_SPANOFBYTES
#include "../../Elysium.Core/Container/View/SpanOfBytes.hpp"
#endif

#ifndef ELYSIUM_CORE_MATH_NUMERICS_BIGINTEGER
#include "../../Elysium.Core.Math/BigInteger.hpp"
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

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1ENUMERATED
#include "Asn1Enumerated.hpp"
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

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1NULL
#include "Asn1Null.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1OBJECTIDENTIFIER
#include "Asn1ObjectIdentifier.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1TAG
#include "Asn1Tag.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1UTF8STRING
#include "Asn1Utf8String.hpp"
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

namespace Elysium::Core::Security::Cryptography::Encoding::Asn1
{
	class ELYSIUM_CORE_SECURITY_API Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Validation::BERValidator;
	class ELYSIUM_CORE_SECURITY_API Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Validation::CERValidator;
	class ELYSIUM_CORE_SECURITY_API Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Validation::DERValidator;
	class ELYSIUM_CORE_SECURITY_API Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Validation::LBERValidator;

	using BERValidator = Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Validation::BERValidator;
	using CERValidator = Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Validation::CERValidator;
	using DERValidator = Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Validation::DERValidator;
	using LBERValidator = Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Validation::LBERValidator;

	template class ELYSIUM_CORE_SECURITY_API Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::BERDecoder<BERValidator>;
	template class ELYSIUM_CORE_SECURITY_API Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::BERDecoder<CERValidator>;
	template class ELYSIUM_CORE_SECURITY_API Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::BERDecoder<DERValidator>;
	template class ELYSIUM_CORE_SECURITY_API Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::BERDecoder<LBERValidator>;

	using BERDecoder = Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::BERDecoder<BERValidator>;
	using CERDecoder = Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::BERDecoder<CERValidator>;
	using DERDecoder = Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::BERDecoder<DERValidator>;
	using LBERDecoder = Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::BERDecoder<LBERValidator>;
}
#endif
