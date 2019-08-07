/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_REFLECCTION_METHODBASE
#define ELYSIUM_CORE_REFLECCTION_METHODBASE

#ifndef ELYSIUM_CORE_REFLECCTION_MEMBERINFO
#include "MemberInfo.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Reflection
		{
			class ELYSIUM_CORE_API MethodBase : public MemberInfo
			{
			public:
				~MethodBase();
			protected:
				MethodBase();
			};
		}
	}
}
#endif
