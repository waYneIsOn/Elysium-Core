/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_OUTOFMEMORYEXCEPTION
#define ELYSIUM_CORE_OUTOFMEMORYEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_EXCEPTION
#include "Exception.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API OutOfMemoryException : public Exception
	{
	public:
		OutOfMemoryException();
		OutOfMemoryException(const char* Message);
		OutOfMemoryException(String&& Message);
		virtual ~OutOfMemoryException();
	};
}
#endif
