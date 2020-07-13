/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

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
		ArithmeticException(const char16_t* Message);
		ArithmeticException(String&& Message);
		virtual ~ArithmeticException();
	};
}
#endif
