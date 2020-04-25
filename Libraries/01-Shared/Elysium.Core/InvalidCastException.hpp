/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

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
		InvalidCastException(const char16_t* Message);
		InvalidCastException(String&& Message);
		virtual ~InvalidCastException();
	};
}
#endif
