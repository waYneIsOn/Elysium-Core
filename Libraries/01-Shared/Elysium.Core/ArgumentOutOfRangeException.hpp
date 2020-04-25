/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_ARGUMENTOUTOFRANGEEXCEPTION
#define ELYSIUM_CORE_ARGUMENTOUTOFRANGEEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_EXCEPTION
#include "Exception.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API ArgumentOutOfRangeException : public Exception
	{
	public:
		ArgumentOutOfRangeException();
		ArgumentOutOfRangeException(const char16_t* Message);
		ArgumentOutOfRangeException(String&& Message);
		virtual ~ArgumentOutOfRangeException();
	};
}
#endif
