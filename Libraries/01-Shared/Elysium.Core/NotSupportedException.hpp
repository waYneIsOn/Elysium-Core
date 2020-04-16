/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_NOTSUPPORTEDEXCEPTION
#define ELYSIUM_CORE_NOTSUPPORTEDEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_EXCEPTION
#include "Exception.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API NotSupportedException : public Exception
	{
	public:
		NotSupportedException();
		NotSupportedException(String&& Message);
		virtual ~NotSupportedException();
	};
}
#endif
