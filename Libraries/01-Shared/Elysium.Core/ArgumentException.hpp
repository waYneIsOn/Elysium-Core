/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_ARGUMENTEXCEPTION
#define ELYSIUM_CORE_ARGUMENTEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_ARGUMENTEXCEPTION
#include "../Elysium.Core.Template/ArgumentException.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API Elysium::Core::Template::Exceptions::ArgumentException;

	using ArgumentException = Elysium::Core::Template::Exceptions::ArgumentException;
}
#endif
