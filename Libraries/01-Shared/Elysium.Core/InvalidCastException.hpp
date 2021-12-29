/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_INVALIDCASTEXCEPTION
#define ELYSIUM_CORE_INVALIDCASTEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_EXCEPTION
#include "Exception.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API InvalidCastException : public Exception
	{
	public:
		InvalidCastException();

		InvalidCastException(const char8_t* Message);

		InvalidCastException(Elysium::Core::Utf8String&& Message);

		virtual ~InvalidCastException();
	};
}
#endif
