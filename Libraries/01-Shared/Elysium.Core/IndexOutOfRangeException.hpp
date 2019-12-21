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

namespace Elysium::Core
{
	class ELYSIUM_CORE_API IndexOutOfRangeException : public Exception
	{
	public:
		IndexOutOfRangeException();
		IndexOutOfRangeException(const String& Message);
		~IndexOutOfRangeException();
	};
}
#endif
