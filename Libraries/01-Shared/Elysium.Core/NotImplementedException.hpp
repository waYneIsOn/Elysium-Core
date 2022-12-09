/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#define ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_EXCEPTION
#include "Exception.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core.Template/NotImplementedException.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API Elysium::Core::Template::Exceptions::NotImplementedException;

	using NotImplementedException = Elysium::Core::Template::Exceptions::NotImplementedException;
}
#endif
