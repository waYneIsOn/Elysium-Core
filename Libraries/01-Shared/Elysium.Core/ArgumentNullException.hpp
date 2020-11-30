/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

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
		ArgumentNullException(const char8_t* Message);
		ArgumentNullException(Elysium::Core::String&& Message);
		virtual ~ArgumentNullException();
	};
}
#endif
