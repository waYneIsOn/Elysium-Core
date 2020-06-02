/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

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

#ifndef ELYSIUM_CORE_SYSTEMEXCEPTION
#include "../Elysium.Core/SystemException.hpp"
#endif

namespace Elysium::Core::Security::Authentication
{
	class ELYSIUM_CORE_SECURITY_API AuthenticationException : public SystemException
	{
	public:
		AuthenticationException();
		AuthenticationException(const char16_t* Message);
		AuthenticationException(String&& Message);
		virtual ~AuthenticationException();
	};
}
#endif
