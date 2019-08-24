/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_ENVIRONMENT
#define ELYSIUM_CORE_ENVIRONMENT

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_OPERATINGSYSTEM
#include "OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		class ELYSIUM_CORE_API Environment final
		{
		public:
			~Environment();

			static String MachineName();
			static OperatingSystem OSVersion();
			static int ProcessorCount();
			static String UserName();
			static String SystemDirectory();
		private:
			Environment();
		};
	}
}
#endif
