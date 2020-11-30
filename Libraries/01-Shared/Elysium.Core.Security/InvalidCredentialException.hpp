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

#ifndef ELYSIUM_CORE_SECURITY_AUTHENTICATION_AUTHENTICATIONEXCEPTION
#include "AuthenticationException.hpp"
#endif

namespace Elysium::Core::Security::Authentication
{
	class ELYSIUM_CORE_SECURITY_API InvalidCredentialException : public AuthenticationException
	{
	public:
		InvalidCredentialException();
		InvalidCredentialException(const char8_t* Message);
		InvalidCredentialException(String&& Message);
		virtual ~InvalidCredentialException();
	};
}
#endif
