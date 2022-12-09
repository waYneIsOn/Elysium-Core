/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SYSTEMEXCEPTION
#define ELYSIUM_CORE_SYSTEMEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_EXCEPTION
#include "Exception.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_SYSTEMEXCEPTION
#include "../Elysium.Core.Template/SystemException.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API Elysium::Core::Template::Exceptions::SystemException;

	using SystemException = Elysium::Core::Template::Exceptions::SystemException;
}
#endif
