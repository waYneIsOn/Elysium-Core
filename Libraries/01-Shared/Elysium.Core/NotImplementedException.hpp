/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#define ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION

#ifndef ELYSIUM_CORE_EXCEPTION
#include "Exception.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		class EXPORT NotImplementedException : public Exception
		{
		public:
			NotImplementedException();
			NotImplementedException(const String& Message);
			~NotImplementedException();
		};
	}
}
#endif
