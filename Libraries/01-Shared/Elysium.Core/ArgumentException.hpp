/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

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

		ArgumentException(const char8_t* Message);

		ArgumentException(Elysium::Core::Utf8String&& Message);

		virtual ~ArgumentException();
	};
}
#endif
