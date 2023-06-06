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

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::Encoding::Asn1
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class Asn1TagClass : Elysium::Core::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
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
