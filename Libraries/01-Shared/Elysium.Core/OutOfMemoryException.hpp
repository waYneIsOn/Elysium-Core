/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_OUTOFMEMORYEXCEPTION
#define ELYSIUM_CORE_OUTOFMEMORYEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_OUTOFMEMORYEXCEPTION
#include "../Elysium.Core.Template/OutOfMemoryException.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API Elysium::Core::Template::Exceptions::OutOfMemoryException;

	using OutOfMemoryException = Elysium::Core::Template::Exceptions::OutOfMemoryException;
}
#endif
