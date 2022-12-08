/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_NOTSUPPORTEDEXCEPTION
#define ELYSIUM_CORE_NOTSUPPORTEDEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_NOTSUPPORTEDEXCEPTION
#include "../Elysium.Core.Template/NotSupportedException.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API Elysium::Core::Template::Exceptions::NotSupportedException;

	using NotSupportedException = Elysium::Core::Template::Exceptions::NotSupportedException;
}
#endif
