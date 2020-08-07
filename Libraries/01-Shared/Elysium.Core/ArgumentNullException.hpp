/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_ARGUMENTNULLEXCEPTION
#define ELYSIUM_CORE_ARGUMENTNULLEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_ARGUMENTEXCEPTION
#include "ArgumentException.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API ArgumentNullException : public ArgumentException
	{
	public:
		ArgumentNullException();
		ArgumentNullException(const char* Message);
		ArgumentNullException(String&& Message);
		virtual ~ArgumentNullException();
	};
}
#endif
