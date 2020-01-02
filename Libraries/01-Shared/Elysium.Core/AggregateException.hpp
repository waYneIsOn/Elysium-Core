/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_AGGREGATEEXCEPTION
#define ELYSIUM_CORE_AGGREGATEEXCEPTION

#ifndef ELYSIUM_CORE_EXCEPTION
#include "Exception.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API AggregateException : public Exception
	{
	public:
		AggregateException();
		AggregateException(const String& Message);
		~AggregateException();
	};
}
#endif
