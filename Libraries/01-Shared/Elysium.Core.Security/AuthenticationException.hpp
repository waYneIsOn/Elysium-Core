/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_AUTHENTICATION_AUTHENTICATIONEXCEPTION
#define ELYSIUM_CORE_SECURITY_AUTHENTICATION_AUTHENTICATIONEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_SECURITY_AUTHENTICATION_AUTHENTICATIONEXCEPTION
#include "../Elysium.Core.Template/Exceptions/Security/Authentication/AuthenticationException.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

namespace Elysium::Core::Security::Authentication
{
	class ELYSIUM_CORE_SECURITY_API Elysium::Core::Template::Exceptions::Security::Authentication::AuthenticationException;

	using AuthenticationException = Elysium::Core::Template::Exceptions::Security::Authentication::AuthenticationException;
}
#endif
