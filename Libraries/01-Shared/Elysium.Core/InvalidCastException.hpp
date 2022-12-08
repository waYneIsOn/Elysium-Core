/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_INVALIDCASTEXCEPTION
#define ELYSIUM_CORE_INVALIDCASTEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_INVALIDCASTEXCEPTION
#include "../Elysium.Core.Template/InvalidCastException.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API Elysium::Core::Template::Exceptions::InvalidCastException;

	using InvalidCastException = Elysium::Core::Template::Exceptions::InvalidCastException;
}
#endif
