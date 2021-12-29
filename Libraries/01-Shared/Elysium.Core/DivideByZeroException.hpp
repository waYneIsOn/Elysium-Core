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

#ifndef ELYSIUM_CORE_ARITHMETICEXCEPTION
#include "ArithmeticException.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API DivideByZeroException : public ArithmeticException
	{
	public:
		DivideByZeroException();
		DivideByZeroException(const char8_t* Message);
		DivideByZeroException(Elysium::Core::Utf8String&& Message);
		virtual ~DivideByZeroException();
	};
}
#endif
