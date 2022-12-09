/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DIVIDEBYZEROEXCEPTION
#define ELYSIUM_CORE_DIVIDEBYZEROEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_ARITHMETICEXCEPTION
#include "ArithmeticException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_DIVIDEBYZEROEXCEPTION
#include "../Elysium.Core.Template/DivideByZeroException.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API Elysium::Core::Template::Exceptions::DivideByZeroException;

	using DivideByZeroException = Elysium::Core::Template::Exceptions::DivideByZeroException;
}
#endif
