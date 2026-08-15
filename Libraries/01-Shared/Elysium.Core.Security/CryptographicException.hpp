/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_CRYPTOGRAPHICEXCEPTION
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_CRYPTOGRAPHICEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_SECURITY_CRYPTOGRAPHY_CRYPTOGRAPHICEXCEPTION
#include "../Elysium.Core.Template/Exceptions/Security/Cryptography/CryptographicException.hpp"
#endif

namespace Elysium::Core::Security::Cryptography
{
	class ELYSIUM_CORE_SECURITY_API Elysium::Core::Template::Exceptions::Security::Cryptography::CryptographicException;

	using CryptographicException = Elysium::Core::Template::Exceptions::Security::Cryptography::CryptographicException;
}
#endif
