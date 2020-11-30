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

#ifndef ELYSIUM_CORE_SYSTEMEXCEPTION
#include "SystemException.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API ArithmeticException : public SystemException
	{
	public:
		ArithmeticException();
		ArithmeticException(const char8_t* Message);
		ArithmeticException(Elysium::Core::String&& Message);
		virtual ~ArithmeticException();
	};
}
#endif
