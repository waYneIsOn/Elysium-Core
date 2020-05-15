/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_SASL_ISASLMECHANISM
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_SASL_ISASLMECHANISM

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "API.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::Asn1
{
	class ELYSIUM_CORE_SECURITY_API ISaslMechanism
	{
	public:
		virtual ~ISaslMechanism() {}
	};
}
#endif
