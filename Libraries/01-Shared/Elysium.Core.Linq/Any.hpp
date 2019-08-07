/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_LINQ_ANY
#define ELYSIUM_CORE_LINQ_ANY

#ifndef ELYSIUM_CORE_COLLECTIONS_IENUMERABLE
#include "../Elysium.Core/IEnumerable.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Linq
		{
			template <class ContainerType>
			bool Any(ContainerType && Container)
			{
				for (auto Element : Container)
				{
					return true;
				}
				return false;
			}
		}
	}
}
#endif
