/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_EXCEPTION
#define ELYSIUM_CORE_EXCEPTION

#ifndef ELYSIUM_CORE_EXPORT
#include "Export.hpp"
#endif

//#ifndef _HAS_EXCEPTIONS
#include <exception>
//#endif

#pragma warning(disable : 4275)

namespace Elysium
{
	namespace Core
	{
		class EXPORT Exception : public std::exception
		{
		public:
			// constructors & destructor
			Exception();
			Exception(const char* Message);
			~Exception();

			// properties - getter
			Exception* GetInnerException();

			// methods
		private:
			// fields
			Exception* _InnerException;
		};
	}
}
#endif
