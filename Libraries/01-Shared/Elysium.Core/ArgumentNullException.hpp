/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_ARGUMENTNULLEXCEPTION
#define ELYSIUM_CORE_ARGUMENTNULLEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_EXCEPTION
#include "Exception.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API ArgumentNullException : public Exception
	{
	public:
		ArgumentNullException();
		ArgumentNullException(const char16_t* Message);
		ArgumentNullException(String&& Message);
		virtual ~ArgumentNullException();
	};
}
#endif
