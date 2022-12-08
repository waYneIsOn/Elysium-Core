/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_ARGUMENTNULLEXCEPTION
#define ELYSIUM_CORE_ARGUMENTNULLEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_ARGUMENTNULLEXCEPTION
#include "../Elysium.Core.Template/ArgumentNullException.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API Elysium::Core::Template::Exceptions::ArgumentNullException;

	using ArgumentNullException = Elysium::Core::Template::Exceptions::ArgumentNullException;
}
#endif
