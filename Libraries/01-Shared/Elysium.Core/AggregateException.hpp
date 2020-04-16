/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_AGGREGATEEXCEPTION
#define ELYSIUM_CORE_AGGREGATEEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_EXCEPTION
#include "Exception.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API AggregateException : public Exception
	{
	public:
		AggregateException();
		AggregateException(String&& Message);
		virtual ~AggregateException();
	};
}
#endif
