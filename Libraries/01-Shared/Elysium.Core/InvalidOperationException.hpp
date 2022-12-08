/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_INVALIDOPERATIONEXCEPTION
#define ELYSIUM_CORE_INVALIDOPERATIONEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_INVALIDOPERATIONEXCEPTION
#include "../Elysium.Core.Template/InvalidOperationException.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API Elysium::Core::Template::Exceptions::InvalidOperationException;

	using InvalidOperationException = Elysium::Core::Template::Exceptions::InvalidOperationException;
}
#endif
