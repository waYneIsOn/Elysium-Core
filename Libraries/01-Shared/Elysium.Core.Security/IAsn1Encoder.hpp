/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_IASN1ENCODER
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_IASN1ENCODER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "API.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::Asn1
{
	class ELYSIUM_CORE_SECURITY_API IAsn1Encoder
	{
	public:
		virtual ~IAsn1Encoder() {}
	};
}
#endif
