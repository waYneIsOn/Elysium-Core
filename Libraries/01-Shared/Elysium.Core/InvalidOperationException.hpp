/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_INVALIDOPERATIONEXCEPTION
#define ELYSIUM_CORE_INVALIDOPERATIONEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_EXCEPTION
#include "Exception.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API InvalidOperationException : public Exception
	{
	public:
		InvalidOperationException();
		InvalidOperationException(const char* Message);
		InvalidOperationException(String&& Message);
		virtual ~InvalidOperationException();
	};
}
#endif
