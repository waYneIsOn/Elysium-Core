/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_INVALIDOPERATIONEXCEPTION
#define ELYSIUM_CORE_INVALIDOPERATIONEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_EXCEPTION
#include "Exception.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API InvalidOperationException : public Exception
	{
	public:
		InvalidOperationException();

		InvalidOperationException(const char8_t* Message);

		InvalidOperationException(Elysium::Core::Utf8String&& Message);

		virtual ~InvalidOperationException();
	};
}
#endif
