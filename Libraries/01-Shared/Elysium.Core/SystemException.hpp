/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_SYSTEMEXCEPTION
#define ELYSIUM_CORE_SYSTEMEXCEPTION

#ifndef ELYSIUM_CORE_EXCEPTION
#include "Exception.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API SystemException : public Exception
	{
	public:
		SystemException();
		SystemException(String&& Message);
		virtual ~SystemException();
	private:
		const unsigned long _HResult;
	};
}
#endif
