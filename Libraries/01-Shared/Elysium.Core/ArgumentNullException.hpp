/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_ARGUMENTNULLEXCEPTION
#define ELYSIUM_CORE_ARGUMENTNULLEXCEPTION

#ifndef ELYSIUM_CORE_EXCEPTION
#include "Exception.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		class ELYSIUM_CORE_API ArgumentNullException : public Exception
		{
		public:
			ArgumentNullException();
			ArgumentNullException(const String& Message);
			~ArgumentNullException();
		};
	}
}
#endif
