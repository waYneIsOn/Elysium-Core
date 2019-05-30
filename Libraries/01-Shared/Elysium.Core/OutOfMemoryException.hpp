/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_OUTOFMEMORYEXCEPTION
#define ELYSIUM_CORE_OUTOFMEMORYEXCEPTION

#ifndef ELYSIUM_CORE_EXCEPTION
#include "Exception.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		class EXPORT OutOfMemoryException : public Exception
		{
		public:
			OutOfMemoryException();
			OutOfMemoryException(const char* Message);
			~OutOfMemoryException();
		};
	}
}
#endif
