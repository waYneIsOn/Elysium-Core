/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_NOTSUPPORTEDEXCEPTION
#define ELYSIUM_CORE_NOTSUPPORTEDEXCEPTION

#ifndef ELYSIUM_CORE_EXCEPTION
#include "Exception.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		class ELYSIUM_CORE_API NotSupportedException : public Exception
		{
		public:
			NotSupportedException();
			NotSupportedException(const String& Message);
			~NotSupportedException();
		};
	}
}
#endif
