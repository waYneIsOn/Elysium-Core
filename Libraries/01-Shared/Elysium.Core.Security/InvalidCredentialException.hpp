/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_AUTHENTICATION_INVALIDCREDENTIALEXCEPTION
#define ELYSIUM_CORE_SECURITY_AUTHENTICATION_INVALIDCREDENTIALEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_SECURITY_AUTHENTICATION_INVALIDCREDENTIALEXCEPTION
#include "../Elysium.Core.Template/Exceptions/Security/Authentication/InvalidCredentialException.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

namespace Elysium::Core::Security::Authentication
{
	class ELYSIUM_CORE_SECURITY_API Elysium::Core::Template::Exceptions::Security::Authentication::InvalidCredentialException;

	using InvalidCredentialException = Elysium::Core::Template::Exceptions::Security::Authentication::InvalidCredentialException;
}
#endif
