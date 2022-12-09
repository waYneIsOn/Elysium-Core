/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_ARGUMENTOUTOFRANGEEXCEPTION
#define ELYSIUM_CORE_ARGUMENTOUTOFRANGEEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_ARGUMENTEXCEPTION
#include "ArgumentException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_ARGUMENTOUTOFRANGEEXCEPTION
#include "../Elysium.Core.Template/ArgumentOutOfRangeException.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API Elysium::Core::Template::Exceptions::ArgumentOutOfRangeException;

	using ArgumentOutOfRangeException = Elysium::Core::Template::Exceptions::ArgumentOutOfRangeException;
}
#endif
