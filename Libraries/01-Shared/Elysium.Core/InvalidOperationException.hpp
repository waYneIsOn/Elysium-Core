/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_INVALIDOPERATIONEXCEPTION
#define ELYSIUM_CORE_INVALIDOPERATIONEXCEPTION

#ifndef ELYSIUM_CORE_EXCEPTION
#include "Exception.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API InvalidOperationException : public Exception
	{
	public:
		InvalidOperationException();
		InvalidOperationException(const char16_t* Message);
		InvalidOperationException(String&& Message);
		virtual ~InvalidOperationException();
	};
}
#endif
