/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_INDEXOUTOFRANGEEXCEPTION
#define ELYSIUM_CORE_INDEXOUTOFRANGEEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_EXCEPTION
#include "Exception.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API IndexOutOfRangeException : public Exception
	{
	public:
		IndexOutOfRangeException();
		IndexOutOfRangeException(const char16_t* Message);
		IndexOutOfRangeException(String&& Message);
		virtual ~IndexOutOfRangeException();
	};
}
#endif
