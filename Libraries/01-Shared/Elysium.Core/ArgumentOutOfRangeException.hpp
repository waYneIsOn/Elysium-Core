/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

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
		ArgumentOutOfRangeException(const char* Message);
		ArgumentOutOfRangeException(String&& Message);
		virtual ~ArgumentOutOfRangeException();
	};
}
#endif
