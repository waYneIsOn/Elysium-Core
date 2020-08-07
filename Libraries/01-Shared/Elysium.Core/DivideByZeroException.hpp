/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_DIVIDEBYZEROEXCEPTION
#define ELYSIUM_CORE_DIVIDEBYZEROEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_ARITHMETICEXCEPTION
#include "ArithmeticException.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API DivideByZeroException : public ArithmeticException
	{
	public:
		DivideByZeroException();
		DivideByZeroException(const char* Message);
		DivideByZeroException(String&& Message);
		virtual ~DivideByZeroException();
	};
}
#endif
