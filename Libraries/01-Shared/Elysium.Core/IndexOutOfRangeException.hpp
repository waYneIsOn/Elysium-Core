/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_INDEXOUTOFRANGEEXCEPTION
#define ELYSIUM_CORE_INDEXOUTOFRANGEEXCEPTION

#ifndef ELYSIUM_CORE_EXCEPTION
#include "Exception.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		class EXPORT IndexOutOfRangeException : public Exception
		{
		public:
			IndexOutOfRangeException();
			IndexOutOfRangeException(const char* Message);
			~IndexOutOfRangeException();
		};
	}
}
#endif
