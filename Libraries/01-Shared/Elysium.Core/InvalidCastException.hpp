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

namespace Elysium
{
	namespace Core
	{
		class EXPORT InvalidCastException : public Exception
		{
		public:
			InvalidCastException();
			InvalidCastException(const char* Message);
			~InvalidCastException();
		};
	}
}
#endif
