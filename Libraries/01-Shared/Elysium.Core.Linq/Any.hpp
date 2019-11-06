/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_LINQ_ANY
#define ELYSIUM_CORE_LINQ_ANY

namespace Elysium
{
	namespace Core
	{
		namespace Linq
		{
			struct AnyContainer
			{
				template<class ContainerType>
				bool operator()(ContainerType && Container)
				{
					for (auto Element : Container)
					{
						return true;
					}
					return false;
				}
			};
		}
	}
}
#endif