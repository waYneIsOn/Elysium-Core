/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#define ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_EXCEPTION
#include "Exception.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API NotImplementedException : public Exception
	{
	public:
		NotImplementedException();
		NotImplementedException(const char* Message);
		NotImplementedException(String&& Message);
		virtual ~NotImplementedException();
	};
}
#endif
