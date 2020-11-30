/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_ARGUMENTOUTOFRANGEEXCEPTION
#define ELYSIUM_CORE_ARGUMENTOUTOFRANGEEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_ARGUMENTEXCEPTION
#include "ArgumentException.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API ArgumentOutOfRangeException : public ArgumentException
	{
	public:
		ArgumentOutOfRangeException();
		ArgumentOutOfRangeException(const char8_t* Message);
		ArgumentOutOfRangeException(Elysium::Core::String&& Message);
		virtual ~ArgumentOutOfRangeException();
	};
}
#endif
