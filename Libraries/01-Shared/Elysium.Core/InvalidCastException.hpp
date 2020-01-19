/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_INVALIDCASTEXCEPTION
#define ELYSIUM_CORE_INVALIDCASTEXCEPTION

#ifndef ELYSIUM_CORE_EXCEPTION
#include "Exception.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API InvalidCastException : public Exception
	{
	public:
		InvalidCastException();
		InvalidCastException(const String& Message);
		virtual ~InvalidCastException();
	};
}
#endif
