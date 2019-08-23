/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_REFLECTION_METHODBASE
#define ELYSIUM_CORE_REFLECTION_METHODBASE

#ifndef ELYSIUM_CORE_REFLECTION_MEMBERINFO
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
