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

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEMEXCEPTION
#include "../Elysium.Core/SystemException.hpp"
#endif

namespace Elysium::Core::Security::Authentication
{
	class ELYSIUM_CORE_SECURITY_API AuthenticationException
		: public SystemException
	{
	public:
		AuthenticationException();

		AuthenticationException(const char8_t* Message);

		AuthenticationException(Elysium::Core::Utf8String&& Message);

		virtual ~AuthenticationException() = default;
	};
}
#endif
