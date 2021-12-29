/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

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
		OutOfMemoryException(const char8_t* Message);
		OutOfMemoryException(Elysium::Core::Utf8String&& Message);
		virtual ~OutOfMemoryException();
	};
}
#endif
