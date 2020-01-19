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

namespace Elysium::Core
{
	class ELYSIUM_CORE_API OutOfMemoryException : public Exception
	{
	public:
		OutOfMemoryException();
		OutOfMemoryException(const String& Message);
		virtual ~OutOfMemoryException();
	};
}
#endif
