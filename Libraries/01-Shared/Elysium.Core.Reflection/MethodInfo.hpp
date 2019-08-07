/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_REFLECCTION_METHODINFO
#define ELYSIUM_CORE_REFLECCTION_METHODINFO

#ifndef ELYSIUM_CORE_REFLECCTION_METHODBASE
#include "MethodBase.hpp"
#endif
namespace Elysium
{
	namespace Core
	{
		namespace Reflection
		{
			class ELYSIUM_CORE_API MethodInfo : public MethodBase
			{
			public:
				~MethodInfo();
			protected:
				MethodInfo();
			};
		}
	}
}
#endif
