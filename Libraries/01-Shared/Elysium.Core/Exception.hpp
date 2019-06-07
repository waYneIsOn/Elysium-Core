/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_EXCEPTION
#define ELYSIUM_CORE_EXCEPTION

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

#pragma warning(disable : 4275)

namespace Elysium
{
	namespace Core
	{
		class ELYSIUM_CORE_API Exception
		{
		public:
			// constructors & destructor
			Exception();
			Exception(const String& Message);
			~Exception();

			// properties - getter
			const Exception* GetInnerException() const;

			// methods
			const String& GetExceptionMessage() const;
		private:
			String _Message;
			Exception* _InnerException;
		};
	}
}
#endif
