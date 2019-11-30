/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_LINQ_COUNT
#define ELYSIUM_CORE_LINQ_COUNT

#ifndef ELYSIUM_CORE_LINQ_API
#include "API.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Linq
		{
			struct ELYSIUM_CORE_LINQ_API CountContainer
			{
				template<class ContainerType>
				size_t operator()(ContainerType && Container)
				{
					size_t Count = 0;
					for (auto Element : Container)
					{
						Count++;
					}
					return Count;
				}
			};
		}
	}
}
#endif
