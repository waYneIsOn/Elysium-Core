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

namespace Elysium
{
	namespace Core
	{
		class ELYSIUM_CORE_API InvalidOperationException : public Exception
		{
		public:
			InvalidOperationException();
			InvalidOperationException(const String& Message);
			~InvalidOperationException();
		};
	}
}
#endif
