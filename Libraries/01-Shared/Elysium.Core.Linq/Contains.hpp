/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_LINQ_CONTAINS
#define ELYSIUM_CORE_LINQ_CONTAINS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_LINQ_API
#include "API.hpp"
#endif

namespace Elysium::Core::Linq
{
	struct ELYSIUM_CORE_LINQ_API ContainsContainer
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
#endif
