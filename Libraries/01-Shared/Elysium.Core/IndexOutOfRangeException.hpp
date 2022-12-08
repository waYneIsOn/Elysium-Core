/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_INDEXOUTOFRANGEEXCEPTION
#define ELYSIUM_CORE_INDEXOUTOFRANGEEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_INDEXOUTOFRANGEEXCEPTION
#include "../Elysium.Core.Template/IndexOutOfRangeException.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API Elysium::Core::Template::Exceptions::IndexOutOfRangeException;

	using IndexOutOfRangeException = Elysium::Core::Template::Exceptions::IndexOutOfRangeException;
}
#endif
