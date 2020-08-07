/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_ARGUMENTEXCEPTION
#define ELYSIUM_CORE_ARGUMENTEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SYSTEMEXCEPTION
#include "SystemException.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API ArgumentException : public SystemException
	{
	public:
		ArgumentException();
		ArgumentException(const char* Message);
		ArgumentException(String&& Message);
		virtual ~ArgumentException();
	};
}
#endif
