/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#define ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION

#ifndef ELYSIUM_CORE_EXCEPTION
#include "Exception.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API NotImplementedException : public Exception
	{
	public:
		NotImplementedException();
		NotImplementedException(const char16_t* Message);
		NotImplementedException(const String& Message);
		~NotImplementedException();
	};
}
#endif
