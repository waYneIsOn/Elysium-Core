/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_OVERFLOWEXCEPTION
#define ELYSIUM_CORE_OVERFLOWEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_ARITHMETICEXCEPTION
#include "ArithmeticException.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API OverflowException : public ArithmeticException
	{
	public:
		OverflowException();
		OverflowException(const char* Message);
		OverflowException(String&& Message);
		virtual ~OverflowException();
	};
}
#endif
