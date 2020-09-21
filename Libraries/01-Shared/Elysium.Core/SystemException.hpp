/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_SYSTEMEXCEPTION
#define ELYSIUM_CORE_SYSTEMEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_EXCEPTION
#include "Exception.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API SystemException : public Exception
	{
	public:
		SystemException();
		SystemException(const char* Message);
		SystemException(Elysium::Core::String&& Message);
		virtual ~SystemException();
	private:
		const unsigned long _HResult;
	};
}
#endif
