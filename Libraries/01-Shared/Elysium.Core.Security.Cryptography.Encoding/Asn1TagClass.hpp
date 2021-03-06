/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1TAGCLASS
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1TAGCLASS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::Encoding::Asn1
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class Asn1TagClass : uint8_t
#elif defined(__ANDROID__)
	enum class Asn1TagClass
#else
#error "undefined os"
#endif
	{
		//Reserved to ASN.1 types
		Universal = 0,

		// Global (top-level) types
		Application = 1,

		// used by default
		Context = 2,

		// rarely used
		Private = 3
	};
}
#endif
