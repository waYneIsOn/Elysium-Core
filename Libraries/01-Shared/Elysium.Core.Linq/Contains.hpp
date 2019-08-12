/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_LINQ_CONTAINS
#define ELYSIUM_CORE_LINQ_CONTAINS

namespace Elysium
{
	namespace Core
	{
		namespace Linq
		{
			struct ContainsContainer
			{
				template<class ContainerType, class ItemType>
				bool operator()(ContainerType && Container, ItemType && Item)
				{
					for (auto Element : Container)
					{
						if (Element == Item)
						{
							return true;
						}
					}
					return false;
				}
			};
		}
	}
}
#endif
