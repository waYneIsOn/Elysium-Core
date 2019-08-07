/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_REFLECCTION_FIELDINFO
#define ELYSIUM_CORE_REFLECCTION_FIELDINFO

#ifndef ELYSIUM_CORE_REFLECCTION_MEMBERINFO
#include "MemberInfo.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Reflection
		{
			class ELYSIUM_CORE_API FieldInfo : public MemberInfo
			{
			public:
				~FieldInfo();
			protected:
				FieldInfo();
			};
		}
	}
}
#endif
