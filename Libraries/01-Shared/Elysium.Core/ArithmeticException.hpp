/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_ARITHMETICEXCEPTION
#define ELYSIUM_CORE_ARITHMETICEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEMEXCEPTION
#include "SystemException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_ARITHMETICEXCEPTION
#include "../Elysium.Core.Template/ArithmeticException.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API Elysium::Core::Template::Exceptions::ArithmeticException;

	using ArithmeticException = Elysium::Core::Template::Exceptions::ArithmeticException;
}
#endif
