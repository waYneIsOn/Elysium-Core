/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_THREADING_SEMAPHOREFULLEXCEPTION
#define ELYSIUM_CORE_THREADING_SEMAPHOREFULLEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_EXCEPTION
#include "../Elysium.Core/Exception.hpp"
#endif

namespace Elysium::Core::Threading
{
	// The exception that is thrown when the Release method is called on a semaphore whose count is already at the maximum.
	class ELYSIUM_CORE_API SemaphoreFullException : public Exception
	{
	public:
		SemaphoreFullException();
		SemaphoreFullException(String&& Message);
		virtual ~SemaphoreFullException();
	};
}
#endif
