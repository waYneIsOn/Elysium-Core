/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_OVERFLOWEXCEPTION
#define ELYSIUM_CORE_OVERFLOWEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_OVERFLOWEXCEPTION
#include "../Elysium.Core.Template/OverflowException.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API Elysium::Core::Template::Exceptions::OverflowException;

	using OverflowException = Elysium::Core::Template::Exceptions::OverflowException;
}
#endif
